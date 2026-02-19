#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpenTriggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->cbTable, &QComboBox::currentIndexChanged, this, &MainWindow::cbTableCurrentIndexChanged);

    initialDirectory = "C:/";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionOpenTriggered()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Datenbank öffnen ...",
        initialDirectory,
        "SQLite-Datenbanken (*.db;*.sqlite);;Alle Dateien (*.*)");
    if (path.isEmpty())
    {
        // no selection
        return;
    }

    bool ok = false;
    const QStringList tables = getAvailableTables(path, ok);
    if (!ok)
    {
        // It's probably not a SQLite database.
        QMessageBox::warning(this, "Fehlerhafte Datei", "Die ausgewählte Datei scheint keine SQLite-Datenbank zu sein. Öffnen abgebrochen.");
        return;
    }

    ui->cbTable->clear();
    for (const QString& tbl: tables)
    {
        ui->cbTable->addItem(tbl);
    }
    dbPath = path;

    ui->tableWidget->clear();
    QString first = *(tables.begin());
    showTableContent(first);

    const QFileInfo fi(path);
    initialDirectory = fi.absolutePath();
}

QStringList MainWindow::getAvailableTables(const QString &dbFile, bool& ok)
{
    QStringList result;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);
    if (!db.open())
    {
        qDebug() << "Fehler beim Öffnen der Datenbank.";
        statusBar()->showMessage("Öffnen der Datenbank ist fehlgeschlagen.", 5000);
        QSqlDatabase::removeDatabase("QSQLITE");
        ok = false;
        return result;
    }

    QSqlQuery query(db);
    // const QString sql = "SELECT seq, name FROM pragma_database_list ORDER BY name ASC;"
    // sqlite_sequence only exists for tables with auto-increment columns.
    // const QString sql = "SELECT name FROM sqlite_sequence ORDER BY name ASC;";
    const QString sql = "SELECT tbl_name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';";
    if (!query.exec(sql))
    {
        qDebug() << "Failed to query available database tables.";
        statusBar()->showMessage("Ermittling der verfügbaren Tabellen in der Datenbank ist fehlgeschlagen.", 5000);
        db.close();
        ok = false;
        QSqlDatabase::removeDatabase("QSQLITE");
        return result;
    }

    while (query.next())
    {
        result.append(query.value("tbl_name").toString());
    }
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");

    ok = true;
    return result;
}

void MainWindow::showTableContent(const QString &table)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "dbPath: " << dbPath;
    db.setDatabaseName(dbPath);
    if (!db.open())
    {
        qDebug() << "Failed to open DB to display content.";
        statusBar()->showMessage("Öffnen der Datenbank fehlgeschlagen", 5000);
        return;
    }

    QString sqlRows = "SELECT COUNT(*) AS numrows FROM " + table + ";";
    qDebug() << sqlRows;
    QSqlQuery query(db);
    if (!query.exec(sqlRows))
    {
        qDebug() << "Query for number of rows failed.";
        const auto error = query.lastError();
        qDebug() << error.text();
        statusBar()->showMessage("Ermittlung der Zeilenanzahl ist fehlgeschlagen: " + error.text(), 5000);
        db.close();
        return;
    }
    query.next();
    const int num_rows = query.value("numrows").toInt();
    qDebug() << "Anzahl Zeilen: " << num_rows;

    if (!query.exec("SELECT * FROM " + table + " LIMIT 1;"))
    {
        qDebug() << "Query for number of columns failed.";
        db.close();
        statusBar()->showMessage("Ermittlung der Spaltenanzahl ist fehlgeschlagen", 5000);
        return;
    }
    const int num_cols = query.record().count();
    qDebug() << "Anzahl Spalten: " << num_cols;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(num_cols);
    ui->tableWidget->setRowCount(num_rows);
    if (!query.exec("SELECT * FROM " + table + ";"))
    {
        qDebug() << "Query for table data failed.";
        statusBar()->showMessage("Abfrage der Daten fehlgeschlagen", 5000);
        return;
    }

    // show field names in header
    QSqlRecord record = query.record();
    for (int c = 0; c < num_cols; ++c)
    {
        QTableWidgetItem* headerItem = new QTableWidgetItem(record.fieldName(c));
        ui->tableWidget->setHorizontalHeaderItem(c, headerItem);
    }

    // add actual data
    int current_row = 0;
    while (query.next())
    {
        for (int c = 0; c < num_cols; ++c)
        {
            const QString value = query.value(c).toString();
            QTableWidgetItem* item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(current_row, c, item);
        }
        ++current_row;
    }
    db.close();
}

void MainWindow::cbTableCurrentIndexChanged(int index)
{
    if (index < 0)
    {
        return;
    }

    QString tableName = ui->cbTable->itemText(index);
    showTableContent(tableName);
}

