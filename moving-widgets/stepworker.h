#ifndef STEPWORKER_H
#define STEPWORKER_H

#include <QObject>
#include "movingwidget.h"

class StepWorker: public QObject
{
    Q_OBJECT
public:
    StepWorker(MovingWidget* widget, QObject* parent = nullptr);

public slots:
    void moveIt();

private:
    MovingWidget* widget;
};

#endif // STEPWORKER_H
