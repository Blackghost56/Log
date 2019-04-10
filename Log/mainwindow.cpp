#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LogCore& instance = LogCore::getInstance();

    instance.add("Main Windows");

    Test t;

    Test tt;

}

MainWindow::~MainWindow()
{
    delete ui;
}
