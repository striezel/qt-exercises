#include "linetrace.h"

LineTrace::LineTrace()
    : colour(Qt::black)
    , width(1)
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

void LineTrace::setWidth(const int new_width)
{
    if (new_width >= 1)
    {
        width = new_width;
    }
}

int LineTrace::getWidth() const
{
    return width;
}

void LineTrace::clear()
{
    points.clear();
}
