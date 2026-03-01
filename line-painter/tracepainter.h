#ifndef TRACEPAINTER_H
#define TRACEPAINTER_H

#include <QList>
#include <QMouseEvent>
#include <QWidget>
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

    void setBackgroundColour(const QColor& background);
    QColor getBackgroundColour() const;

    /// Clears existing line traces.
    void clearTraces();
private:
    Ui::TracePainter *ui;

    QList<LineTrace> traces;
    QColor background;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent *event) override;

};

#endif // TRACEPAINTER_H
