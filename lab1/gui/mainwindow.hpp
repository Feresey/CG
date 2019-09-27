#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;
    ~MainWindow();

private slots:
    void myslot(double = 0);

private:
    Ui::MainWindow* ui;
};

#endif
