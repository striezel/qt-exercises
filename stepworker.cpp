#include "stepworker.h"

StepWorker::StepWorker(MovingWidget* widget, QObject* parent)
    : QObject(parent)
    , widget(widget)
{
}

void StepWorker::moveIt()
{
    if (widget != nullptr)
    {
        widget->moveOneStep();
    }
}
