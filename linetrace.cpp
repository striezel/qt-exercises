#include "linetrace.h"

LineTrace::LineTrace()
{
    points.clear();
}

void LineTrace::add(const QPoint &pt)
{
    points.append(pt);
}
