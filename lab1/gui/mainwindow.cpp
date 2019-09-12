#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    close->setKey(QKeySequence("Esc"));
    connect(close, SIGNAL(activated()), this, SLOT(close()));
    // connect(ui->big, &QPushButton::clicked, &OGLWidget::bigger);
    // connect(ui->CalculationButton, SIGNAL(clicked()), this, SLOT(myslot()));
    // connect(ui->big,SIGNAL(clicked(bool)),ui->openGLWidget, SLOT(bigger(bool)));
    // connect(ui->small,SIGNAL(clicked()),ui->openGLWidget, SLOT(smaller()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myslot()
{
    ui->ErrorLabel->setText("");

    bool ok;
    double a, b, A, B, scale, step;
    a = ui->input_a->text().toDouble(&ok);
    if (!ok)
        ui->ErrorLabel->setText(QString::fromUtf8("Number a is not double"));

    b = ui->input_b->text().toDouble(&ok);
    if (!ok)
        ui->ErrorLabel->setText(QString::fromUtf8("Number b is not double"));

    if (a >= b) {
        ui->ErrorLabel->setText(QString::fromUtf8("'b' should be greater than 'a'"));
        return;
    }
    A = ui->input_A->text().toDouble(&ok);
    if (!ok)
        ui->ErrorLabel->setText(QString::fromUtf8("Number A is not double"));

    B = ui->input_B->text().toDouble(&ok);
    if (!ok)
        ui->ErrorLabel->setText(QString::fromUtf8("Number B is not double"));

    // scale = ui->scale_slider-> ->text().toDouble(&ok);
    // if (!ok)
    //     ui->ErrorLabel->setText(QString::fromUtf8("Number Bscale is not double"));

    step = ui->input_step->text().toDouble(&ok);
    if (!ok)
        ui->ErrorLabel->setText(QString::fromUtf8("Number step is not double"));

    ui->openGLWidget->set(a, b, A, B, step);
    ui->openGLWidget->update();
}

void MainWindow::resize(int a)
{
    ui->openGLWidget->resize(1 + double(a) / 100);
    ui->openGLWidget->update();
}