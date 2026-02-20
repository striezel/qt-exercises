#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QWidget>

namespace Ui {
class MovableWidget;
}

class MovableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovableWidget(QWidget *parent = nullptr);
    ~MovableWidget();

private:
    Ui::MovableWidget *ui;
};

#endif // MOVABLEWIDGET_H
