#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include "movingwidget.h"
#include "stepworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showEvent(QShowEvent* event) override;

signals:
    void doTheNextMove();

private:
    Ui::MainWindow *ui;

    MovingWidget* widgetOne;
    MovingWidget* widgetTwo;
    void btnMoveClicked();

    QThread threadOne;
    QThread threadTwo;

    StepWorker* workerOne = nullptr;
    StepWorker* workerTwo = nullptr;

    QTimer timer;
};
#endif // MAINWINDOW_H
