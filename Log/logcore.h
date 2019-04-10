#ifndef LOGCORE_H
#define LOGCORE_H

#include <QObject>
#include <QDebug>

class LogCore
{
private:
    LogCore();
    LogCore(const LogCore&) = delete;
    LogCore& operator=(LogCore&) = delete;
public:
    static LogCore &getInstance();
    void add(const QString &str);
    //LogCore();
};

#endif // LOGCORE_H
