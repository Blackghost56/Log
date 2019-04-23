#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logcore.h"
#include "test.h"
#include "testqobject.h"
#include <QThread>
#include "testthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TestThread *th1;
    TestThread *th2;

};



#endif // MAINWINDOW_H
