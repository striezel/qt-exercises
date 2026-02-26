#include "stepworker.h"

StepWorker::StepWorker(QObject* parent)
    : QObject(parent)
{
    timer.setInterval(250);
}
