#include "logcore.h"

LogCore::LogCore()
{

}

LogCore &LogCore::getInstance()
{
    static LogCore  instance;
    return instance;
}

void LogCore::add(const QString &str)
{
    qDebug() << str;
    //qDebug("const char *msg %s", "32");
    //qDebug() << str << __FILE__ << __LINE__ << Q_FUNC_INFO;

    //qInfo() << "info";

    //fprintf(stderr, "%s\n", "asd");
    //fprintf(stdout, "%s\n", "asd");

}

void LogCore::addData(const LogCore::LogData &data)
{
    qDebug() << "Group: "   << LogGroupString.value(data.group);
    qDebug() << "Context: " << data.context;
    qDebug() << "Msg: "     << data.msg;
}

LogMsg::LogMsg(const char *file, int line, const char *function)
{
    stream.setString(&data.msg, QIODevice::ReadWrite);

    data.context = QString("File: %1  Line: %2  Function: %3").arg(file).arg(line).arg(function);
    //context.push_back(QString(file + QString::number(line) + function));
    //context.push_back(QString("File: %1  Line: %2  Function: %3").arg(file).arg(line).arg(function));
}

LogMsg::~LogMsg()
{
    LogCore& log = LogCore::getInstance();
    log.addData(data);
    //log.add(msg);
    //log.add(stream.readAll());
    //log.data.msg = stream.readAll();
    //data.msg = stream.readAll();
}

LogMsg &LogMsg::Debug()
{
    //context.push_back("  Debug: ");
    //stream << context;
    data.group = LogCore::LogGroup::Debug;

    return *this;
}

LogMsg &LogMsg::Info()
{
    //context.push_back("  Info: ");
    //stream << context;
    data.group = LogCore::LogGroup::Info;

    return *this;
}

