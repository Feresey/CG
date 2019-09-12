#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#define CHECK(STR)                                                                \
    if (!ok) {                                                                    \
        ui->ErrorLabel->setText(QString::fromUtf8("Number " STR " is not double")); \
        return;                                                                   \
    }

void MainWindow::myslot()
{
    ui->ErrorLabel->setText("");

    bool ok;
    double a, b, A, B, step;

    a = ui->input_a->text().toDouble(&ok);
    CHECK("a")
    b = ui->input_b->text().toDouble(&ok);
    CHECK("b")
    if (a >= b) {
        ui->ErrorLabel->setText(QString::fromUtf8("'b' should be greater than 'a'"));
        return;
    }

    A = ui->input_A->text().toDouble(&ok);
    CHECK("A")
    B = ui->input_B->text().toDouble(&ok);
    CHECK("B")
    step = ui->input_step->text().toDouble(&ok);
    CHECK("step")

    ui->openGLWidget->set(a, b, A, B, step);
    ui->openGLWidget->update();
}

void MainWindow::resize(int a)
{
    ui->openGLWidget->resize(1 + double(a) / 100);
    ui->openGLWidget->update();
}

void MainWindow::grow()
{
    ui->openGLWidget->setSeed(0.001);
    ui->openGLWidget->update();
}

void MainWindow::reduce()
{
    ui->openGLWidget->setSeed(-0.001);
    ui->openGLWidget->update();
}