#include "logcore.h"


LogCore::LogCore(QObject *parent) : QObject(parent)
{
   workerThread = new QThread;
   worker = new LogHandler();

   worker->moveToThread(workerThread);

   //connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
   //connect(this, &LogCore::send, worker, &LogHandler::doWork);
   connect(this, SIGNAL(send(LogCore::LogData &)), worker, SLOT(doWork(LogCore::LogData &)));

   workerThread->start();
}

LogCore::~LogCore()
{
    delete worker;
    workerThread->quit();
    workerThread->wait();
}

LogCore &LogCore::getInstance()
{
    static LogCore  instance;
    return instance;
}

void LogCore::addData(const LogCore::LogData &data)
{
    mutex.lock();
    LogData buf = data;

    if ((buf.category != "Default") && (!buf.category.isEmpty()))
    {
        if (!categories.contains(buf.category))
            categories.push_back(buf.category);
        buf.category = buf.category;
    } else {
        if (!checkObjectIsBinded(buf.ptr, buf.category) && (buf.category != "Default"))
            buf.category = "Default";
    }
    //qDebugOut(buf);
    emit send(buf);
    mutex.unlock();
}

bool LogCore::checkObjectIsBinded(const QObject *ptr, QString &category)
{
    if (ptr == nullptr)
        return false;

    bool buf = false;

    if (catptr.contains(ptr))
    {
        category = catptr.value(ptr);
        buf = true;
    }

    return buf;
}

void LogCore::qDebugOut(const LogCore::LogData &data)
{
    qDebug() << "Group: "       << LogGroupString.value(data.group);
    qDebug() << "Category: "    << data.category;
    qDebug() << "Context: "     << data.context;
    qDebug() << "Ptr: "         << data.ptr <<  "Ptr&: "  << &data.ptr << "Ptr& + 1: "  << &data.ptr + 1;
    qDebug() << "Msg: "         << data.msg;
    qDebug() << "";
}

void LogCore::bindQObjectWithCategory(const QString &category, const QObject *ptr)
{
    categories.push_back(category);
    catptr.insert(ptr, category);
}

LogHandler::LogHandler()
{
    qRegisterMetaType<LogCore::LogData>("LogCore::LogData &");

    logFile.setFileName("Log_"  + QDateTime::currentDateTimeUtc().toString("dd_MM_yyyy__hh_mm_ss_UTC") + ".txt");
    if (!logFile.open(QIODevice::WriteOnly))
    {
        // Dummy: write 'error create log file' to ui log
        return;
    }
    writeStream.setDevice(&logFile);


    //qDebug() << "LogHandler";
    //writeStream  << "Test 3";
    //writeStream.flush();
}

LogHandler::~LogHandler()
{
    qDebug() << "LogHandler destructor";
    logFile.close();
}

void LogHandler::doWork(LogCore::LogData &data)
{
    //qDebug() << "doWork";
    //qDebug() << "Group: "       << LogGroupString.value(data.group);
    /*qDebug() << "Category: "    << data.category;
                qDebug() << "Context: "     << data.context;
                qDebug() << "Ptr: "         << data.ptr <<  "Ptr&: "  << &data.ptr << "Ptr& + 1: "  << &data.ptr + 1;
                qDebug() << "Msg: "         << data.msg;
                qDebug() << "";*/
    writeToFile(data);
}

void LogHandler::writeToFile(LogCore::LogData &data)
{
    //qDebug() << "WriteToFile";
    writeStream << data.time.toString("hh:mm:ss.zz") << endl;
    writeStream << data.group << endl;
    writeStream << data.context << endl;
    writeStream << data.category << endl;
    writeStream << data.msg << endl << endl;

    writeStream.flush();
}

LogMsg::LogMsg(const char *file, int line, const char *function, const QObject *ptr)
{
    stream.setString(&data.msg, QIODevice::ReadWrite);

    data.time = QTime::currentTime();
    data.context = QString("File: %1  Line: %2  Function: %3").arg(file).arg(line).arg(function);
    data.ptr = ptr;
}

LogMsg::~LogMsg()
{
    LogCore& log = LogCore::getInstance();
    log.addData(data);
}

LogMsg &LogMsg::Debug()
{
    data.group = LogCore::LogGroup::Debug;

    return *this;
}

LogMsg &LogMsg::Debug(const QString &category)
{
    data.group = LogCore::LogGroup::Debug;
    data.category = category;

    return *this;
}

LogMsg &LogMsg::Info()
{
    data.group = LogCore::LogGroup::Info;

    return *this;
}

LogMsg &LogMsg::Info(const QString &category)
{
    data.group = LogCore::LogGroup::Info;
    data.category = category;

    return *this;
}


