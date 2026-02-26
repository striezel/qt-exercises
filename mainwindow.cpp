#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widgetOne = new MovingWidget(ui->centralwidget);
    widgetOne->setEdge(Qt::TopEdge);
    widgetOne->setDirection(MovingWidget::Direction::Clockwise);

    widgetTwo = new MovingWidget(ui->centralwidget);
    widgetTwo->setEdge(Qt::BottomEdge);
    widgetTwo->setDirection(MovingWidget::Direction::CounterClockwise);

    connect(ui->btnMove, &QPushButton::clicked, this, &MainWindow::btnMoveClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    // Here we use setEdge() trigger the private adjustPosition() method in the
    // widgets, because the parent's (i.e. central widget's) layout may still be
    // incomplete during the constructor.
    if (widgetOne != nullptr)
    {
        widgetOne->setEdge(widgetOne->getEdge());
        widgetTwo->setEdge(widgetTwo->getEdge());
    }
}

void MainWindow::btnMoveClicked()
{
    for (int i = 0; i < 5; ++ i)
    {
        widgetOne->moveOneStep();
        widgetTwo->moveOneStep();
    }
}
