#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QColor>
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

    /// Set pointer to other widget - used in collision detection.
    void setOther(MovableWidget* other);

    void setCollidingColour(const QColor col);
    void setCollisionFreeColour(const QColor col);

    QColor getCollidingColour() const;
    QColor getCollisionFreeColour() const;

    /// colour when widget collides with other widget
    static const QColor defaultCollidingColour;

    /// colour when widget does not collide
    static const QColor defaultCollisionFreeColour;

private:
    Ui::MovableWidget *ui;

    // Position of last mouse button press.
    QPoint position;

    // pointer to other movable widget (if any)
    const MovableWidget* other;

    QColor collidingColour;
    QColor collisionFreeColour;

    // Checks whether the widget collides with the other widget.
    // If so, the colour of the widget changes.
    //
    // Note: You need to set the widget to check for collisions by calling
    // setOther() and passing a pointer to said widget.
    void collisionDetection();

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // MOVABLEWIDGET_H
