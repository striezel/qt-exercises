#ifndef STEPWORKER_H
#define STEPWORKER_H

#include <QObject>
#include <QTimer>

class StepWorker: public QObject
{
    Q_OBJECT
public:
    StepWorker(QObject* parent = nullptr);

private:
    QTimer timer;
};

#endif // STEPWORKER_H
