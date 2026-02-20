#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QMouseEvent>
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

    // Position of last mouse button press.
    QPoint position;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // MOVABLEWIDGET_H
