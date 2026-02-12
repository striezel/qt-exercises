#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sliderRed, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);
    connect(ui->sliderGreen, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);
    connect(ui->sliderBlue, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::btnResetClicked);
    connect(ui->btnRandomize, &QPushButton::clicked, this, &MainWindow::btnRandomizeClicked);

    btnResetClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sliderValueChanged(int value)
{
    ui->lblRedValue->setText(QString::number(ui->sliderRed->value()));
    ui->lblGreenValue->setText(QString::number(ui->sliderGreen->value()));
    ui->lblBlueValue->setText(QString::number(ui->sliderBlue->value()));

    updateColourLabel();
}

void MainWindow::updateColourLabel()
{
    const int r = ui->sliderRed->value();
    const int g = ui->sliderGreen->value();
    const int b = ui->sliderBlue->value();

    QPalette palette = this->palette();
    palette.setColor(QPalette::ColorRole::Window, QColor(r, g, b));
    ui->lblColour->setPalette(palette);

    updateHexValue(r, g, b);
}

void MainWindow::updateHexValue(const int r, const int g, const int b)
{
    // Everybody hates printf-style format specifiers.
    // But this it C++17 and not C++20, so no std::format() is available here.
    QString hex = QString::asprintf("0x%02X%02X%02X", r, g, b);
    ui->lblHexValue->setText(hex);
}


void MainWindow::btnResetClicked()
{
    ui->sliderRed->setValue(127);
    ui->sliderGreen->setValue(127);
    ui->sliderBlue->setValue(127);
}

void MainWindow::btnRandomizeClicked()
{
    ui->sliderRed->setValue(QRandomGenerator::global()->bounded(0, 256));
    ui->sliderGreen->setValue(QRandomGenerator::global()->bounded(0, 256));
    ui->sliderBlue->setValue(QRandomGenerator::global()->bounded(0, 256));
}
