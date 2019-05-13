#include "logcore.h"


LogCore::LogCore(QObject *parent) : QObject(parent)
{

    for (int i = 0; i < LogGroup::last; i++)
    {
        filterState.groupState.insert(LogGroupToString(i), newGroupStateDefault);
    }


    workerThread = new QThread;
    //worker = new LogHandler(this);
    worker = new LogHandler();
    worker->moveToThread(workerThread);
    connect(this, &LogCore::sendToWorker, worker, &LogHandler::doWork);
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
    mutexAdd.lock();
    LogData buf = data;

    /*if ((buf.category != "Default") && (!buf.category.isEmpty()))
    {
        if (!categories.contains(buf.category)){
            mutexCat.lock();
            mutexFilter.lock();
            categories.push_back(buf.category);
            filterState.categoriesState.insert(buf.category, newCategoriesStateDefault);
            emit categoriesHasChanged(categories, filterState.categoriesState);
            mutexFilter.unlock();
            mutexCat.unlock();
        }
        buf.category = buf.category;
    } else {
        if (!checkObjectIsBinded(buf.ptr, buf.category) && (buf.category != "Default"))
            buf.category = "Default";
    }*/
    if (!buf.category.isEmpty())
        {
            if (!categories.contains(buf.category)){
                mutexCat.lock();
                mutexFilter.lock();
                categories.push_back(buf.category);
                filterState.categoriesState.insert(buf.category, newCategoriesStateDefault);
                emit categoriesHasChanged(categories, filterState.categoriesState);
                mutexFilter.unlock();
                mutexCat.unlock();
            }
            buf.category = buf.category;
        } else {
            if (!checkObjectIsBinded(buf.ptr, buf.category))
                buf.category = "Default";
        }
    //qDebugOut(buf);
    emit sendToWorker(buf);
    mutexAdd.unlock();
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

/*void LogCore::qDebugOut(const LogCore::LogData &data)
{
    qDebug() << "Group: "       << LogCoreInstance.LogGroupToString(data.group);
    qDebug() << "Category: "    << data.category;
    qDebug() << "Context: "     << data.context;
    qDebug() << "Ptr: "         << data.ptr <<  "Ptr&: "  << &data.ptr << "Ptr& + 1: "  << &data.ptr + 1;
    qDebug() << "Msg: "         << data.msg;
    qDebug() << "";
}*/

void LogCore::bindQObjectWithCategory(const QString &category, const QObject *ptr)
{
    QMutexLocker locker(&mutexCat);
    categories.push_back(category);
    catptr.insert(ptr, category);
    mutexFilter.lock();
    filterState.categoriesState.insert(category, newCategoriesStateDefault);
    emit categoriesHasChanged(categories, filterState.categoriesState);
    mutexFilter.unlock();
}

QString LogCore::LogGroupToString(const int &group)
{
    QMutexLocker locker(&mutexLGTS);
    QString buf = LogGroupString.value(group);
    return buf;
}

QVector<QString> LogCore::getCategories()
{
    QMutexLocker locker(&mutexCat);

    return categories;
}

LogHandler *LogCore::getLogHandlerPtr()
{
    return worker;
}

LogCore::Filter &LogCore::getFilterState()
{
    QMutexLocker locker(&mutexFilter);

    return filterState;
}

void LogCore::setFilterState(const LogCore::Filter &state)
{
    QMutexLocker locker(&mutexFilter);
    filterState = state;
    // debug!!!!!!!!!!
    /*QString buf;
    qDebug() << "groupState:";
    for (int i = 0; i < LogCore::LogGroup::last; i++)
    {
        buf = LogGroupToString(i);
        qDebug() << buf << state.groupState.value(buf);
    }
    qDebug() << "categoriesState:";
    for (auto i: categories)
    {
        qDebug() << i << state.categoriesState.value(i);
    }
    qDebug() << "timePrefixVisible: " << state.timePrefixVisible;
    qDebug() << "groupPrefixVisible: " << state.groupPrefixVisible;
    qDebug() << "contextPrefixVisible: " << state.contextPrefixVisible;
    qDebug() << "categoriesPrefixVisible: " << state.categoriesPrefixVisible;*/

}

LogHandler::LogHandler()
{
    qRegisterMetaType<LogCore::LogData>("LogCore::LogData &");

    //connect(this, &LogHandler::serviceInformation, static_cast<LogCore *>(parent), &LogCore::sendStringToUi);
    //connect(this, &LogHandler::serviceInformation, static_cast<LogCore *>(parent), &LogCore::test);

    QString date = QDateTime::currentDateTimeUtc().toString("dd_MM_yyyy__hh_mm_ss_UTC");
    QString filename = "Log_"  + date + ".txt";
    logFile.setFileName(filename);
    //logFile.setFileName("Log_:wasd:sda:\|.txt");
    if (!logFile.open(QIODevice::WriteOnly))
    {
        // Dummy: write 'error create log file' to ui log
        //emit serviceInformation("Error open log file");
        return;
    }
    //qDebug() << "serviceInformation";
    //emit serviceInformation("Log file is open. File name: " + filename + "      File directory : " + QDir::currentPath());
    //qDebug() << "Log file is open. File name: " + filename + "     File directory : " + QDir::currentPath();
    writeStream.setDevice(&logFile);
}

LogHandler::~LogHandler()
{
    //qDebug() << "LogHandler destructor";
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
    //emit sendDataToUi(filterData(data));
    sendFilteredDataToUi(data);
}

void LogHandler::writeToFile(const LogCore::LogData &data)
{
    //qDebug() << "WriteToFile";
    if (writeStream.device() == nullptr){
        return;
    }
    writeStream << data.time.toString(time_format_1) << endl;
    writeStream << LogCoreInstance.LogGroupToString(data.group) << endl;
    writeStream << data.context << endl;
    writeStream << data.category << endl;
    writeStream << data.msg << endl << endl;

    writeStream.flush();
}

void LogHandler::sendFilteredDataToUi(const LogCore::LogData &data)
{
    QString buf;
    LogCore &logCoreRef = LogCore::getInstance();
    LogCore::Filter filter = logCoreRef.getFilterState();

    if (filter.groupState.value(logCoreRef.LogGroupToString(data.group)) && filter.categoriesState.value(data.category))
    {
        if (filter.timePrefixVisible)
            buf.push_back(data.time.toString(time_format_2));

        if (filter.contextPrefixVisible)
            buf.push_back(" " + data.context);

        if (filter.groupPrefixVisible)
            buf.push_back(" " + logCoreRef.LogGroupToString(data.group));

        if (filter.categoriesPrefixVisible)
            buf.push_back(" " + data.category);

        buf.push_back("> ");

        buf.push_back(data.msg);

        emit sendDataToUi(buf);
    }
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

LogMsg &LogMsg::Warning()
{
    data.group = LogCore::LogGroup::Warning;

    return *this;
}

LogMsg &LogMsg::Warning(const QString &category)
{
    data.group = LogCore::LogGroup::Warning;
    data.category = category;

    return *this;
}

LogMsg &LogMsg::Critical()
{
    data.group = LogCore::LogGroup::Critical;

    return *this;
}

LogMsg &LogMsg::Critical(const QString &category)
{
    data.group = LogCore::LogGroup::Critical;
    data.category = category;

    return *this;
}

LogMsg &LogMsg::Fatal()
{
    data.group = LogCore::LogGroup::Fatal;

    return *this;
}

LogMsg &LogMsg::Fatal(const QString &category)
{
    data.group = LogCore::LogGroup::Fatal;
    data.category = category;

    return *this;
}


