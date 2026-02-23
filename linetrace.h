#ifndef LINETRACE_H
#define LINETRACE_H

#include <QColor>
#include <QPoint>
#include <QList>

struct LineTrace
{
public:
    LineTrace();

    QList<QPoint> points;

    /// Adds another point to the end of the line trace.
    void add(const QPoint& pt);

    /// Sets the colour of the line trace.
    /// The value must be a valid QColor, otherwise it is ignored.
    void setColour(const QColor& colour);

    /// Gets the trace's current colour.
    QColor getColour() const;
private:
    QColor colour;
};

#endif // LINETRACE_H
