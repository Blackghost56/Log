#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //LogCore& log = LogCore::getInstance();
    //LogMsg logm = LogMsg();


    //LogMsg() << "str 1" << " str 2";

    //LogAddCategory("s");
    //LogAddCategory("ss");

    LogBindQObject("d");

    LogDebug() << "str 1" << " str 2 " << 5;
    LogInfo() << "str 3" << " str 4";
    LogInfo("Cat 1") << 546 << "   striiiinnng";

    LogDebugQOC() << "QOC test 1";
    LogDebugQOC("s") << "QOC test 2";





    th1 = new TestThread("1", this);
    th2 = new TestThread("2", this);

    th1->start();
    th2->start();
}

MainWindow::~MainWindow()
{
    //delete pthread;
    delete ui;
}
