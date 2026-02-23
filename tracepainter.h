#ifndef TRACEPAINTER_H
#define TRACEPAINTER_H

#include <QWidget>
#include <QMouseEvent>
#include "linetrace.h"

namespace Ui {
class TracePainter;
}

class TracePainter : public QWidget
{
    Q_OBJECT

public:
    explicit TracePainter(QWidget *parent = nullptr);
    ~TracePainter();

    LineTrace& currentTrace();

private:
    Ui::TracePainter *ui;

    LineTrace trace;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent *event) override;

};

#endif // TRACEPAINTER_H
