#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <sine_signal.h>
#include <wavheader.h>
#include "adaptive_resolution_vector.hpp"
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void timer_event();

private:

    std::vector<bool> get_message();
    int get_PM_size();

    Ui::MainWindow *ui;

    QTimer timer;
    PM_signal s;

    adaptive_resolution_vector<double,1024> error_with_time;
};
#endif // MAINWINDOW_H
