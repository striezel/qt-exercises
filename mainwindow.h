#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void sliderValueChanged(int value);

    void btnResetClicked();

private:
    Ui::MainWindow *ui;

    void updateColourLabel();
};
#endif // MAINWINDOW_H
