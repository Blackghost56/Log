#ifndef LOGCORE_H
#define LOGCORE_H

#include <QObject>
#include <QDebug>

class LogCore
{
private:
    LogCore();
    LogCore(const LogCore&) = delete;
    LogCore& operator = (LogCore&) = delete;
public:
    static LogCore &getInstance();

    //void operator << (const QString &str){ add(str); }

    LogCore& operator << (const QString &str){
        add(str);
        return *this;
    }

    void add(const QString &str);


};


class LogMsg
{
private:
    QString msg;
    QString context;
public:
    enum MsgType {debug, info, warning, critical, fatal};
    LogMsg(const char *file, int line, const char *function);
    LogMsg& push();
    LogMsg& push(MsgType);

    LogMsg& operator << (const QString &str){
        msg.append(str);
        return *this;
    }
};


#define FILE static_cast<const char *>(__FILE__)
#define LINE __LINE__
#define FUNC static_cast<const char *>(Q_FUNC_INFO)
#define cLog LogMsg(FILE, LINE, FUNC).push

#endif // LOGCORE_H
