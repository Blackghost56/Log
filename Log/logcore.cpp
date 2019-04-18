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
    qDebug("const char *msg %s", "32");
    //qDebug() << str << __FILE__ << __LINE__ << Q_FUNC_INFO;

    //qInfo() << "info";

    //fprintf(stderr, "%s\n", "asd");
    //fprintf(stdout, "%s\n", "asd");

}

LogMsg::LogMsg(const char *file, int line, const char *function)
{
    context.push_back(QString(file + QString::number(line) + function));
}

LogMsg &LogMsg::push()
{
    LogCore& log = LogCore::getInstance();
    log.add(msg);

    return *this;
}

LogMsg &LogMsg::push(LogMsg::MsgType)
{
    LogCore& log = LogCore::getInstance();
    log.add(msg);

    return *this;
}
