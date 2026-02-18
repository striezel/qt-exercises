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
    QSet<QString> tables = getAvailableTables(path, ok);
    if (!ok)
    {
        // It's probably not a SQLite database.
        QMessageBox::warning(this, "Fehlerhafte Datei", "Die ausgewählte Datei scheint keine SQLite-Datenbank zu sein. Öffnen abgebrochen.");
        return;
    }

    ui->cbTable->clear();
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
        ok = false;
        return result;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT seq, name FROM pragma_database_list ORDER BY name ASC;"))
    {
        qDebug() << "Failed to query available databases.";
        db.close();
        ok = false;
        return result;
    }

    while (query.next())
    {
        result.insert(query.value("name").toString());
    }
    db.close();

    ok = true;
    return result;
}
