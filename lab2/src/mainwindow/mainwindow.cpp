// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "mainwindow.hpp"
#include "../ui/ui_mainwindow.h"

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
