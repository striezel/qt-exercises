#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionChangeColour, &QAction::triggered, this, &MainWindow::actionChangeColourTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionChangeColourTriggered()
{
    const QColor new_colour = QColorDialog::getColor(
        ui->paintWidget->currentTrace().getColour(),
        this,
        "Farbe für aktuellen Linienstrang wählen"
        );

    ui->paintWidget->currentTrace().setColour(new_colour);
    update();
}
