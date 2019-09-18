// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto collapse = new QShortcut(this);
    collapse->setKey(QKeySequence("Esc"));
    connect(collapse, SIGNAL(activated()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myslot(double)
{
    ui->input_b->setMinimum(ui->input_a->value());
    ui->input_a->setMaximum(ui->input_b->value());
    double a, b, A, B, step;

    a = ui->input_a->value();
    b = ui->input_b->value();
    if (a >= b) {
        ui->statusbar->showMessage("'b' should be greater than 'a'");
        return;
    }

    A = ui->input_A->value();
    B = ui->input_B->value();
    step = ui->input_step->value();
    if (step < 0.00001) {
        ui->statusbar->showMessage("step is too small");
        return;
    }
    ui->openGLWidget->set(a, b, A, B, step);
    ui->openGLWidget->update();
    ui->statusbar->showMessage("");
}
