#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionChangeCollisionColour, &QAction::triggered, this, &MainWindow::actionChangeCollisionColourTriggered);
    connect(ui->actionChangeCollisionFreeColour, &QAction::triggered, this, &MainWindow::actionChangeCollisionFreeColourTriggered);

    ui->widget->setOther(ui->widgetTwo);
    ui->widgetTwo->setOther(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionChangeCollisionColourTriggered()
{
    const QColor newColour = QColorDialog::getColor(
        ui->widget->getCollidingColour(),
        this, "Farbe für Kollisionen auswählen");
    ui->widget->setCollidingColour(newColour);
    ui->widgetTwo->setCollidingColour(newColour);
}

void MainWindow::actionChangeCollisionFreeColourTriggered()
{
    const QColor newColour = QColorDialog::getColor(
        ui->widget->getCollisionFreeColour(),
        this, "Farbe für Rechteck ohne Kollision auswählen");
    ui->widget->setCollisionFreeColour(newColour);
    ui->widgetTwo->setCollisionFreeColour(newColour);
}
