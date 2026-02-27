#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionStartMovement, &QAction::triggered, this, &MainWindow::startMovement);
    connect(ui->actionStopMovement, &QAction::triggered, this, &MainWindow::stopMovement);
    connect(ui->actionChangeColourWidgetOne, &QAction::triggered, this, &MainWindow::changeColourWidgetOne);
    connect(ui->actionChangeColourWidgetTwo, &QAction::triggered, this, &MainWindow::changeColourWidgetTwo);

    widgetOne = new MovingWidget(ui->centralwidget);
    widgetOne->setEdge(Qt::TopEdge);
    widgetOne->setDirection(MovingWidget::Direction::Clockwise);
    widgetOne->setColour(QColor(0, 0, 255));

    widgetTwo = new MovingWidget(ui->centralwidget);
    widgetTwo->setEdge(Qt::BottomEdge);
    widgetTwo->setDirection(MovingWidget::Direction::CounterClockwise);
    widgetTwo->setColour(QColor(255, 255, 0));

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

void MainWindow::startMovement()
{
    timer.start();
}

void MainWindow::stopMovement()
{
    timer.stop();
}

void MainWindow::changeColourWidgetOne()
{
    const QColor newColour = QColorDialog::getColor(widgetOne->getColour(),
                                    this, "Farbe des ersten Widgets wählen");
    widgetOne->setColour(newColour);
}

void MainWindow::changeColourWidgetTwo()
{
    const QColor newColour = QColorDialog::getColor(widgetTwo->getColour(),
                                                    this, "Farbe des zweiten Widgets wählen");
    widgetTwo->setColour(newColour);
}
