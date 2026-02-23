#include "tracepainter.h"
#include "ui_tracepainter.h"
#include <QPainter>

TracePainter::TracePainter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TracePainter)
{
    ui->setupUi(this);

    setMouseTracking(true);
}

TracePainter::~TracePainter()
{
    delete ui;
}

void TracePainter::mousePressEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        trace.add(event->pos());
        update();
    }
}

void TracePainter::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        trace.add(event->pos());
        update();
    }
}

void TracePainter::paintEvent(QPaintEvent *event)
{
    this->QWidget::paintEvent(event);

    const qsizetype count = trace.points.count();
    if (count < 2)
    {
        return;
    }

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::NoBrush));

    for (qsizetype i = 1; i < count; i++)
    {
        const QPoint start = trace.points[i - 1];
        const QPoint end = trace.points[i];
        painter.drawLine(start, end);
    }
}
