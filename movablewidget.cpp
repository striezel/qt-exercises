#include "movablewidget.h"
#include "ui_movablewidget.h"

const QColor MovableWidget::collidingColour = QColor(255, 0, 0);
const QColor MovableWidget::collisionFreeColour = QColor(0, 156, 0);

MovableWidget::MovableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovableWidget)
    , other(nullptr)
{
    ui->setupUi(this);
    // Required to make sure we get mouse events also when no button is pressed.
    this->setMouseTracking(true);
}

MovableWidget::~MovableWidget()
{
    delete ui;
}

void MovableWidget::setOther(MovableWidget *other)
{
    if (other != this)
    {
        this->other = other;
    }
}

void MovableWidget::collisionDetection()
{
    if (other == nullptr)
    {
        return;
    }

    /*qDebug() << "\nGeometry: " << this->geometry();
    qDebug() << "Rect:     " << this->rect();
    qDebug() << "Pos:      " << this->pos();*/

    const QPoint selfGlobal = this->mapToGlobal(this->rect().topLeft());
    const QRect selfGlobalRect = QRect(selfGlobal, this->size());
    // qDebug() << "Self: " << selfGlobalRect;

    const QPoint otherGlobal = other->mapToGlobal(other->rect().topLeft());
    const QRect otherGlobalRect = QRect(otherGlobal, other->size());
    // qDebug() << "Other: " << otherGlobalRect;

    if (selfGlobalRect.intersects(otherGlobalRect))
    {
        // qDebug() << "Collides!";
        QPalette palette = this->palette();
        palette.setColor(QPalette::ColorRole::Window, collidingColour);
        this->setPalette(palette);
    }
    else
    {
        // qDebug() << "No collision.";
        QPalette palette = this->palette();
        palette.setColor(QPalette::ColorRole::Window, collisionFreeColour);
        this->setPalette(palette);
    }
}

void MovableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        const QPoint newPosition = event->pos();
        const QPoint delta = newPosition - position;
        const QPoint posInParent = this->mapToParent(delta);
        this->move(posInParent);

        collisionDetection();
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
