#include "logcore.h"


//LogCore::LogCore(QObject *pobj) : QObject (pobj)
LogCore::LogCore()
{
   /*QThread *thread= new QThread;
   LogHandler *my = new LogHandler("B");

   my->moveToThread(thread);

   connect(my, SIGNAL(send(int)), this, SLOT(update(int)));
   connect(thread, SIGNAL(started()), my, SLOT(doWork()));

   thread->start();*/
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

/*void LogCore::addCategory(const QString &category)
{
    qDebug() << "addCategory: " << category;
}*/

void LogCore::bindQObjectWithCategory(const QString &category, const QObject *ptr)
{
    //qDebug() << "bindQObjectWithCategory: " << category << "  ptr: " << ptr;

    //categories.insert(category, ptr);
    categories.push_back(category);
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
