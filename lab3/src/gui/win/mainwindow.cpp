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
    connect(collapse, &QShortcut::activated, std::bind(&MainWindow::close, this));
    ui->x_box->SetAxis('x');
    ui->y_box->SetAxis('y');
    ui->z_box->SetAxis('z');

    ui->light_x->SetProd(1);
    ui->light_y->SetProd(1);
    ui->light_z->SetProd(1);
    ui->light_x->SetAxis('x');
    ui->light_y->SetAxis('y');
    ui->light_z->SetAxis('z');
}

MainWindow::~MainWindow()
{
    delete ui;
}
