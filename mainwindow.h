#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

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
    void actionChangeLineColourTriggered();
    void actionChangeBackgroundColourTriggered();
    void actionChangeWidthTriggered();

    void actionSaveAsImageTriggered();

private:
    Ui::MainWindow *ui;

    QActionGroup* widthActionGroup;
};
#endif // MAINWINDOW_H
