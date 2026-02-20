#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setOther(ui->widgetTwo);
    ui->widgetTwo->setOther(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
