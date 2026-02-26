#include "movingwidget.h"
#include "ui_movingwidget.h"

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
}

MovingWidget::Direction MovingWidget::getDirection() const
{
    return direction;
}
