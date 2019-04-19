#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //LogCore& log = LogCore::getInstance();
    //LogMsg logm = LogMsg();

    //log.add("Main Windows");
    //log << "Main Windows";
    /*logm << "Str1" << " Str2";
    log << "Main Windows" << "12 s";
    logm << " Str3";
    logm.push() << "F";
    logm.push();*/

    //LogMsg() << "str 1" << " str 2";

    //LogAddCategory("s");
    //LogAddCategory("ss");

    LogBindQObject("d");

    LogDebug() << "str 1" << " str 2 " << 5;
    LogInfo() << "str 3" << " str 4";
    LogInfo("Cat 1") << 546 << "   striiiinnng";

    LogDebugQOC() << "QOC test 1";
    LogDebugQOC("s") << "QOC test 2";


    TestQObject TestQ;
    //qDebug() << this;

    //Test t;

    //Test tt;

}

MainWindow::~MainWindow()
{
    delete ui;
}
