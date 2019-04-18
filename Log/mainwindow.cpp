#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LogCore& log = LogCore::getInstance();
    //LogMsg logm = LogMsg();

    //log.add("Main Windows");
    //log << "Main Windows";
    /*logm << "Str1" << " Str2";
    log << "Main Windows" << "12 s";
    logm << " Str3";
    logm.push() << "F";
    logm.push();*/

    //LogMsg() << "str 1" << " str 2";
    cLog() << "str 1" << " str 2";
    cLog() << "str 3" << " str 4";

    Test t;

    Test tt;

}

MainWindow::~MainWindow()
{
    delete ui;
}
