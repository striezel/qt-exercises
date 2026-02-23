#include "linetrace.h"

LineTrace::LineTrace()
    : colour(Qt::black)
{
    points.clear();
}

void LineTrace::add(const QPoint &pt)
{
    points.append(pt);
}

void LineTrace::setColour(const QColor &colour)
{
    if (colour.isValid())
    {
        this->colour = colour;
    }
}

QColor LineTrace::getColour() const
{
    return colour;
}
