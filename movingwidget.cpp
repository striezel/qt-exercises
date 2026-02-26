#include "movingwidget.h"
#include "ui_movingwidget.h"

#include <QDebug>

MovingWidget::MovingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovingWidget)
    , edge(Qt::TopEdge)
    , direction(Direction::Clockwise)
{
    ui->setupUi(this);

    adjustPosition();
}

MovingWidget::~MovingWidget()
{
    delete ui;
}

Qt::Edge MovingWidget::getEdge() const
{
    return edge;
}

void MovingWidget::setEdge(const Qt::Edge edge)
{
    this->edge = edge;
    adjustPosition();
}

void MovingWidget::setDirection(const Direction dir)
{
    direction = dir;
}

void MovingWidget::moveOneStep()
{
    const QWidget* parentW = this->parentWidget();
    if (parentW == nullptr)
    {
        return;
    }

    QPoint newPos = pos();
    switch (edge)
    {
    case Qt::Edge::TopEdge:
        newPos.setX(newPos.x() + (direction == Direction::Clockwise)
                    - (direction == Direction::CounterClockwise));
        break;
    case Qt::Edge::LeftEdge:
        newPos.setY(newPos.y() - (direction == Direction::Clockwise)
                    + (direction == Direction::CounterClockwise));
        break;
    case Qt::Edge::RightEdge:
        newPos.setY(newPos.y() + (direction == Direction::Clockwise)
                    - (direction == Direction::CounterClockwise));
        break;
    case Qt::Edge::BottomEdge:
        newPos.setX(newPos.x() - (direction == Direction::Clockwise)
                    + (direction == Direction::CounterClockwise));
        break;
    }

    this->move(newPos);
}

void MovingWidget::adjustPosition()
{
    const QWidget* parentW = this->parentWidget();

    switch (edge)
    {
    case Qt::Edge::TopEdge:
        move(this->pos().x(), 0);
        break;
    case Qt::Edge::LeftEdge:
        this->move(0, pos().y());
        break;
    case Qt::Edge::RightEdge:
        if (parentW == nullptr)
        {
            return;
        }
        this->move(parentW->rect().width() - this->rect().width(),  pos().y());
        break;
    case Qt::Edge::BottomEdge:
        if (parentW == nullptr)
        {
            return;
        }
        this->move(pos().x(), parentW->rect().height() - this->rect().height());
        break;
    }

    qDebug() << "Position: " << pos().x() << "," << pos().y();
}

MovingWidget::Direction MovingWidget::getDirection() const
{
    return direction;
}
