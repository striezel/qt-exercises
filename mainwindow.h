#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movingwidget.h"

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

private:
    Ui::MainWindow *ui;

    MovingWidget* widgetOne;
    MovingWidget* widgetTwo;
    void btnMoveClicked();
};
#endif // MAINWINDOW_H
