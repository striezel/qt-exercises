#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpenTriggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionOpenTriggered()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Datenbank öffnen ...",
        "C:/",
        "SQLite-Datenbanken (*.db;*.sqlite);;Alle Dateien (*.*)");
    if (path.isEmpty())
    {
        // no selection
        return;
    }

    bool ok = false;
    const QSet<QString> tables = getAvailableTables(path, ok);
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
    ui->tableWidget->clear();
}

QSet<QString> MainWindow::getAvailableTables(const QString &dbFile, bool& ok)
{
    QSet<QString> result;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);
    if (!db.open())
    {
        qDebug() << "Fehler beim Öffnen der Datenbank.";
        QSqlDatabase::removeDatabase("QSQLITE");
        ok = false;
        return result;
    }

    QSqlQuery query(db);
    // const QString sql = "SELECT seq, name FROM pragma_database_list ORDER BY name ASC;"
    const QString sql = "SELECT name FROM sqlite_sequence ORDER BY name ASC;";
    if (!query.exec(sql))
    {
        qDebug() << "Failed to query available databases.";
        db.close();
        ok = false;
        QSqlDatabase::removeDatabase("QSQLITE");
        return result;
    }

    while (query.next())
    {
        result.insert(query.value("name").toString());
    }
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");

    ok = true;
    return result;
}
