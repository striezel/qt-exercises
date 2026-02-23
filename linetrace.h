#ifndef LINETRACE_H
#define LINETRACE_H

#include <QPoint>
#include <QList>

struct LineTrace
{
public:
    LineTrace();

    QList<QPoint> points;

    void add(const QPoint& pt);
};

#endif // LINETRACE_H
