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

    /*LogBindQObject("d");

    LogDebug() << "str 1" << " str 2 " << 5;
    LogInfo() << "str 3" << " str 4";
    LogInfo("Cat 1") << 546 << "   striiiinnng";

    LogDebugQOC() << "QOC test 1";
    LogDebugQOC("s") << "QOC test 2";*/

    // unit test 1
    LogBindQObject("LogBindQObject");

    LogDebug() << "LogDebug";
    LogInfo() << "LogInfo";
    LogWarning() << "LogWarning";
    LogCritical() << "LogCritical";
    LogFatal() << "LogFatal";

    LogInfo() << "str 3" << " str 4";
    LogInfo("Cat 1") << 546;

    LogDebugQOC() << "QOC test 1";
    LogDebugQOC("s") << "QOC test 2";
    // -----------

    // unit test 2
    LogInfo("String")           << "str 1"          << " str 2";
    LogInfo("QChar")            << QChar('c');
    LogInfo("char")             << 'z';
    LogInfo("bool")             << false;
    LogInfo("signed short")     << short(-12)       << short(35u);
    LogInfo("unsigned short")   << ushort(-12u)     << ushort(35u);
    LogInfo("signed int")       << int(-1200)       << int(35);
    LogInfo("unsigned int")     << uint(-1200u)     << uint(35u);
    LogInfo("signed long")      << -1200L           << 35L;
    LogInfo("unsigned long")    << -1200UL          << 35UL;
    LogInfo("qint64")           << qint64(-1200)    << qint64(35);
    LogInfo("quint64")          << quint64(-1200)   << quint64(35);
    LogInfo("float")            << float(-12.3554);
    LogInfo("double")           << double(-12.2222222222222222222111111) << double(-12222.2222222222222222111111);
    LogInfo("float to QString") << QString("%1").arg(double(float(-12222.2222222222222222111111)), 0, 'g', 30);
    LogInfo("double to QString")<< QString("%1").arg(double(-12222.2222222222222222111111), 0, 'g', 30);
    // -----------


    th1 = new TestThread("Thread 1", this);
    th2 = new TestThread("Thread 2", this);

    //th1->start();
    //th2->start();
}

MainWindow::~MainWindow()
{
    //delete pthread;
    delete ui;
}
