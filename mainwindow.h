#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QString>

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
    void actionOpenTriggered();

private:
    Ui::MainWindow *ui;

    //QSet<QString> getAvailableTables(const QString& dbFile, bool& ok);
};
#endif // MAINWINDOW_H
