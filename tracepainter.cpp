#include "tracepainter.h"
#include "ui_tracepainter.h"
#include <QPainter>

TracePainter::TracePainter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TracePainter)
    , background(Qt::white)
{
    ui->setupUi(this);

    setMouseTracking(true);

    traces.append(LineTrace());
}

TracePainter::~TracePainter()
{
    delete ui;
}

LineTrace& TracePainter::currentTrace()
{
    return traces.last();
}

void TracePainter::setBackgroundColour(const QColor &background)
{
    if (background.isValid())
    {
        this->background = background;
    }
}

QColor TracePainter::getBackgroundColour() const
{
    return background;
}

void TracePainter::mousePressEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        const QColor previous_colour = traces.isEmpty()
        ? Qt::GlobalColor::black
        : traces.last().getColour();
        if (traces.isEmpty() || traces.last().points.count() >= 2)
        {
            LineTrace nextTrace = LineTrace();
            nextTrace.setColour(previous_colour);
            traces.append(nextTrace);
        }

        traces.last().add(event->pos());
        update();
    }
}

void TracePainter::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0)
    {
        traces.last().add(event->pos());
        update();
    }
}

void TracePainter::paintEvent(QPaintEvent *event)
{
    this->QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::PenStyle::NoPen));
    painter.setBrush(background);
    painter.drawRect(this->rect());

    for (qsizetype n_trace = 0; n_trace<traces.count(); ++ n_trace)
    {
        const LineTrace& trace = traces.at(n_trace);
        const qsizetype count = trace.points.count();
        if (count < 2)
        {
            continue;
        }

        painter.setBrush(QBrush(Qt::NoBrush));
        painter.setPen(trace.getColour());

        for (qsizetype i = 1; i < count; i++)
        {
            const QPoint start = trace.points[i - 1];
            const QPoint end = trace.points[i];
            painter.drawLine(start, end);
        }
    }
}
