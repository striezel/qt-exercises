#ifndef MOVINGWIDGET_H
#define MOVINGWIDGET_H

#include <QWidget>

namespace Ui {
class MovingWidget;
}

class MovingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovingWidget(QWidget *parent = nullptr);
    ~MovingWidget();

    Qt::Edge getEdge() const;
    void setEdge(const Qt::Edge edge);

    enum class Direction
    {
        Clockwise,
        CounterClockwise
    };

    Direction getDirection() const;
    void setDirection(const Direction dir);

    QColor getColour() const;
    void setColour(const QColor& colour);

    void moveOneStep();

private:
    Ui::MovingWidget *ui;

    Qt::Edge edge;
    Direction direction;
    QColor colour;

    void adjustPosition();
};

#endif // MOVINGWIDGET_H
