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
        // Adjust position.
        newPos.setX(newPos.x() + (direction == Direction::Clockwise)
                    - (direction == Direction::CounterClockwise));
        // Change direction, if we met the end of the edge.
        if ((direction == Direction::CounterClockwise) && (newPos.x() <= 0))
        {
            edge = Qt::Edge::LeftEdge;
        }
        else if ((direction == Direction::Clockwise) && (newPos.x() >= parentW->rect().width() - this->rect().width()))
        {
            edge = Qt::Edge::RightEdge;
        }
        break;
    case Qt::Edge::LeftEdge:
        newPos.setY(newPos.y() - (direction == Direction::Clockwise)
                    + (direction == Direction::CounterClockwise));
        if ((direction == Direction::Clockwise) && (newPos.y() <= 0))
        {
            edge = Qt::Edge::TopEdge;
        }
        else if ((direction == Direction::CounterClockwise) && (newPos.y() >= parentW->rect().height() - this->rect().height()))
        {
            edge = Qt::Edge::BottomEdge;
        }
        break;
    case Qt::Edge::RightEdge:
        newPos.setY(newPos.y() + (direction == Direction::Clockwise)
                    - (direction == Direction::CounterClockwise));
        if ((direction == Direction::CounterClockwise) && (newPos.y() <= 0))
        {
            edge = Qt::Edge::TopEdge;
        }
        else if ((direction == Direction::Clockwise) && (newPos.y() >= parentW->rect().height() - this->rect().height()))
        {
            edge = Qt::Edge::BottomEdge;
        }
        break;
    case Qt::Edge::BottomEdge:
        newPos.setX(newPos.x() - (direction == Direction::Clockwise)
                    + (direction == Direction::CounterClockwise));
        // Change direction, if we met the end of the edge.
        if ((direction == Direction::Clockwise) && (newPos.x() <= 0))
        {
            edge = Qt::Edge::LeftEdge;
        }
        else if ((direction == Direction::CounterClockwise) && (newPos.x() >= parentW->rect().width() - this->rect().width()))
        {
            edge = Qt::Edge::RightEdge;
        }
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
