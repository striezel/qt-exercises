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

    timer.setInterval(25);

    workerOne = new StepWorker(widgetOne, this);
    workerTwo = new StepWorker(widgetTwo, this);

    workerOne->moveToThread(&threadOne);
    workerTwo->moveToThread(&threadTwo);

    connect(&timer, &QTimer::timeout, this, [this] {
        emit doTheNextMove();
    });

    connect(this, &MainWindow::doTheNextMove, workerOne, &StepWorker::moveIt);
    connect(this, &MainWindow::doTheNextMove, workerTwo, &StepWorker::moveIt);
}

MainWindow::~MainWindow()
{
    if (threadOne.isRunning())
    {
        threadOne.quit();
        threadOne.wait();
    }
    if (threadTwo.isRunning())
    {
        threadTwo.quit();
        threadTwo.wait();
    }

    delete workerOne;
    delete workerTwo;

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

    // start the timer
    timer.start();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (widgetOne != nullptr)
    {
        widgetOne->setEdge(widgetOne->getEdge());
        widgetTwo->setEdge(widgetTwo->getEdge());
    }
}
