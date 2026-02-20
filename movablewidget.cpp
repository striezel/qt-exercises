#include "movablewidget.h"
#include "ui_movablewidget.h"

MovableWidget::MovableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovableWidget)
{
    ui->setupUi(this);
}

MovableWidget::~MovableWidget()
{
    delete ui;
}
