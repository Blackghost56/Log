#include "logcore.h"


LogCore::LogCore()
{

}

LogCore &LogCore::getInstance()
{
    static LogCore  instance;
    return instance;
}

/*void LogCore::add(const QString &str)
{
    qDebug() << str;
    //qDebug("const char *msg %s", "32");
    //qDebug() << str << __FILE__ << __LINE__ << Q_FUNC_INFO;

    //qInfo() << "info";

    //fprintf(stderr, "%s\n", "asd");
    //fprintf(stdout, "%s\n", "asd");

}*/

void LogCore::addData(const LogCore::LogData &data)
{
    qDebug() << "Group: "       << LogGroupString.value(data.group);
    qDebug() << "Category: "    << data.category;
    qDebug() << "Context: "     << data.context;
    qDebug() << "Ptr: "         << data.ptr <<  "Ptr&: "  << &data.ptr << "Ptr& + 1: "  << &data.ptr + 1;
    qDebug() << "Msg: "         << data.msg;
    //qDebug() << "";

    LogData buf;
    QString buf_cat;

    if ((data.category != "Default") && (!data.category.isEmpty()))
    {
        buf.category = data.category;
    } else if (ObjectIsBinded(buf.ptr, buf_cat)) {
        buf.category = buf_cat;
    }

    //qDebug() << "Group: "       << LogGroupString.value(data.group);
    qDebug() << "Category: "    << buf.category;
    //qDebug() << "Context: "     << data.context;
    //qDebug() << "Ptr: "         << data.ptr <<  "Ptr&: "  << &data.ptr << "Ptr& + 1: "  << &data.ptr + 1;
    //qDebug() << "Msg: "         << data.msg;
    qDebug() << "";
}

bool LogCore::ObjectIsBinded(const QObject *ptr, QString &category)
{
    bool buf = false;

    if (catptr.contains(ptr))
    {
        category = catptr.value(ptr);
        buf = true;
    }

    return buf;
}

/*void LogCore::addCategory(const QString &category)
{
    qDebug() << "addCategory: " << category;
}*/

void LogCore::bindQObjectWithCategory(const QString &category, const QObject *ptr)
{
    qDebug() << "bindQObjectWithCategory: " << category << "  ptr: " << ptr;

    categories.insert(category, ptr);
    catptr.insert(ptr, category);
    /*QMap<QString, const QObject *>::const_iterator i = categories.find(category);
    if (i == categories.end())                              // Availability item check
    {
        categories.insert(category, ptr);
    } else {

    }*/
    /*if (categories.find(category) != categories.end())
    {
        QList<const QObject *> values = categories.values(category);
        for (int i = 0; i < values.size(); ++i)
            qDebug() << values.at(i) << endl;
    }*/
}

LogMsg::LogMsg(const char *file, int line, const char *function, const QObject *ptr)
{
    stream.setString(&data.msg, QIODevice::ReadWrite);

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
