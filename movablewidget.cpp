#include "movablewidget.h"
#include "ui_movablewidget.h"

MovableWidget::MovableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovableWidget)
{
    ui->setupUi(this);
    // Required to make sure we get mouse events also when no button is pressed.
    this->setMouseTracking(true);
}

MovableWidget::~MovableWidget()
{
    delete ui;
}

void MovableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        const QPoint newPosition = event->pos();
        const QPoint delta = newPosition - position;
        const QPoint posInParent = this->mapToParent(delta);
        this->move(posInParent);
    }
}

void MovableWidget::mousePressEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        // LMB was or still is pressed.
        position = event->pos();
    }
}
