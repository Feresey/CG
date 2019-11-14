#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto collapse = new QShortcut(this);
    collapse->setKey(QKeySequence("Esc"));
    connect(collapse, SIGNAL(activated()), this, SLOT(close()));
    ui->x_box->SetAxis('x');
    ui->y_box->SetAxis('y');
    ui->z_box->SetAxis('z');
}

MainWindow::~MainWindow()
{
    delete ui;
}
