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
}
