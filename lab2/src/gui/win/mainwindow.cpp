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
}

MainWindow::~MainWindow()
{
    delete ui;
}
