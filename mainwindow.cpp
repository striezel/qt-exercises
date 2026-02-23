#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionSaveAsImage, &QAction::triggered, this, &MainWindow::actionSaveAsImageTriggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionChangeLineColour, &QAction::triggered, this, &MainWindow::actionChangeLineColourTriggered);
    connect(ui->actionChangeBackgroundColour, &QAction::triggered, this, &MainWindow::actionChangeBackgroundColourTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionChangeLineColourTriggered()
{
    const QColor new_colour = QColorDialog::getColor(
        ui->paintWidget->currentTrace().getColour(),
        this,
        "Farbe für aktuellen Linienstrang wählen"
        );

    ui->paintWidget->currentTrace().setColour(new_colour);
    update();
}

void MainWindow::actionChangeBackgroundColourTriggered()
{
    const QColor new_colour = QColorDialog::getColor(
        ui->paintWidget->getBackgroundColour(),
        this, "Hintergrundfarbe wählen");

    ui->paintWidget->setBackgroundColour(new_colour);
    update();
}

void MainWindow::actionSaveAsImageTriggered()
{
    QString imageFileName = QFileDialog::getSaveFileName(
        this,
        "Als PNG-Datei speichern ...",
        QDir::homePath(),
        "PNG-Datei (*.png);;Alle Dateien (*.*)");

    qDebug() << "File: " << imageFileName;
    if (imageFileName.isEmpty())
    {
        return;
    }

    QPixmap pix = ui->paintWidget->grab();
    if (!pix.save(imageFileName))
    {
        QMessageBox::warning(
            this, "Speichern fehlgeschlagen",
            "Das Gemälde konnte nicht unter " + imageFileName + " gespeichert werden.");
    }
}
