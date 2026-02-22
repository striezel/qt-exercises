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

    void btnRandomizeClicked();

private:
    Ui::MainWindow *ui;

    void updateColourLabel();
    void updateHexValue(const int r, const int g, const int b);
};
#endif // MAINWINDOW_H
