// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "mainwindow.hpp"
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
    ui->y_box->setX(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myslot(double)
{
    double a, b, A, B;
    int points;

    a = ui->input_a->value();
    b = ui->input_b->value();
    ui->input_b->setMinimum(a);
    ui->input_a->setMaximum(b);
    if (a >= b) {
        ui->statusbar->showMessage("'b' should be greater than 'a'");
        return;
    }

    A = ui->input_A->value();
    B = ui->input_B->value();
    if (A > B) {
        ui->statusbar->showMessage("'B' should be greater than 'A'");
        return;
    }
    points = ui->input_points->value();

    ui->openGLWidget->calculate(a, b, A, B, points);
    ui->openGLWidget->update();
    ui->statusbar->showMessage("");
}
