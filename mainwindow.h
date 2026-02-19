#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>

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

    void cbTableCurrentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QString dbPath;
    QString initialDirectory;

    QStringList getAvailableTables(const QString& dbFile, bool& ok);

    void showTableContent(const QString& table);
};
#endif // MAINWINDOW_H
