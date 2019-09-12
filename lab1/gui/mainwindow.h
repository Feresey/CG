#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtWidgets/QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void myslot();
    void resize(int a);
    void grow();
    void reduce();

private:
    Ui::MainWindow* ui;
    // QShortcut *close = new QShortcut(this);

};

#endif // MAINWINDOW_H
