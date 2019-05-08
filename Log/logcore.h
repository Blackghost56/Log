#ifndef LOGCORE_H
#define LOGCORE_H

#include <QObject>
#include <QDebug>       //!!!
#include <QVector>
#include <QTextStream>
#include <QIODevice>
#include <QMutex>
#include <QThread>
#include <QFile>
#include <QDateTime>
#include <QDir>



class LogHandler;

class LogCore : public QObject
{
    Q_OBJECT
public:
    enum LogGroup : int {Debug, Info, Warning, Critical, Fatal};
    QMap<int, QString> LogGroupString = {{Debug, "Debug"}, {Info, "Info"}, {Warning, "Warning"}, {Critical, "Critical"}, {Fatal, "Fatal"}};

    struct LogData
    {
        LogData () : category("Default"), ptr(nullptr) {}
        QTime time;
        QString msg;
        QString context;
        LogGroup group;
        QString category;
        const QObject *ptr;
    };

    struct Filter {
        bool timePrefixVisible       = true;
        bool contextPrefixVisible    = false;
        QMap<QString, bool> categoriesState;
        bool categoriesPrefixVisible = true;
        QMap<LogGroup, bool> groupState = {{Debug, true}, {Info, true}, {Warning, true}, {Critical, true}, {Fatal, true}};
        bool groupPrefixVisible = false;
    };

private:
    const bool  newCategoriesStateDefault = true;

    QMutex mutexAdd;
    QMutex mutexLGTS;
    QMutex mutexCat;
    QMutex mutexFilter;
    QVector<QString> categories;
    QMap<const QObject *, QString> catptr;
    QThread *workerThread;
    LogHandler *worker;
    Filter filterState;

    bool checkObjectIsBinded(const QObject *ptr, QString &category);
    //void qDebugOut(const LogData &data);

    LogCore(QObject *parent = nullptr);
    LogCore(const LogCore&) = delete;
    LogCore& operator = (LogCore&) = delete;
    ~LogCore();
public:
    static LogCore &getInstance();
    void addData(const LogData &data);
    void bindQObjectWithCategory(const QString &category, const QObject *ptr);
    QString LogGroupToString(const LogGroup &group);
    QVector<QString> getCategories();
    LogHandler *getLogHandlerPtr();
    Filter &getFilterState();
    void setFilterState(const Filter &state);


signals:
    void sendToWorker(LogCore::LogData &);
    void categoriesHasChanged(const QVector<QString> &categories, const QMap<QString, bool> categoriesState);
    //void sendStringToUi(const QString &str);

public slots:

};



class LogHandler : public QObject
{
    Q_OBJECT
private:
    const QString time_format_1 = "hh:mm:ss.zz";
    const QString time_format_2 = "hh:mm:ss.zzz";

    QFile           logFile;
    QTextStream     writeStream;

    void writeToFile(const LogCore::LogData &data);
    void sendFilteredDataToUi(const LogCore::LogData &data);

public:
    LogHandler();
    //LogHandler(QObject *parent = nullptr);
    ~LogHandler();

public slots:
    void doWork(LogCore::LogData &data);

signals:
    void serviceInformation(const QString &str);
    //void sendDataToUi(const LogCore::LogData &data);
    void sendDataToUi(const QString &data);
};

#define LogCoreInstance LogCore::getInstance()
#define LogBindUI(UIPtr) \
                connect(&LogCoreInstance, &LogCore::categoriesHasChanged, UIPtr, &LogWidget::categoriesHasChanged); \
                connect(LogCoreInstance.getLogHandlerPtr(), &LogHandler::sendDataToUi, UIPtr, &LogWidget::addString);
                /*connect(&LogCoreInstance, &LogCore::sendStringToUi, UIPtr, &LogWidget::addString);*/
#define LogBindQObject(category) \
                LogCore::getInstance().bindQObjectWithCategory(category, this);


#define FILE static_cast<const char *>(__FILE__)
#define LINE __LINE__
#define FUNC static_cast<const char *>(Q_FUNC_INFO)

#define LogDebug LogMsg(FILE, LINE, FUNC).Debug
#define LogInfo LogMsg(FILE, LINE, FUNC).Info
#define LogWarning LogMsg(FILE, LINE, FUNC).Warning
#define LogCritical LogMsg(FILE, LINE, FUNC).Critical
#define LogFatal LogMsg(FILE, LINE, FUNC).Fatal

#define LogDebugQOC LogMsg(FILE, LINE, FUNC, this).Debug
#define LogInfoQOC LogMsg(FILE, LINE, FUNC, this).Info
#define LogWarningQOC LogMsg(FILE, LINE, FUNC, this).Warning
#define LogCriticalQOC LogMsg(FILE, LINE, FUNC, this).Critical
#define LogFatalQOC LogMsg(FILE, LINE, FUNC, this).Fatal

class LogMsg
{
protected:
    QTextStream stream;
    LogCore::LogData data;

public:
    LogMsg(const char *file, int line, const char *function, const QObject *ptr = nullptr);
    ~LogMsg();
    LogMsg &Debug();
    LogMsg &Debug(const QString &category);
    LogMsg &Info();
    LogMsg &Info(const QString &category);
    LogMsg &Warning();
    LogMsg &Warning(const QString &category);
    LogMsg &Critical();
    LogMsg &Critical(const QString &category);
    LogMsg &Fatal();
    LogMsg &Fatal(const QString &category);


    LogMsg &space() { stream << ' '; return *this; }
    LogMsg &operator << (const QString &str) { stream << str; return space(); }
    LogMsg &operator << (const QChar &t) { stream << t; return space(); }
    LogMsg &operator << (const char &t) { stream << t; return space(); }
    LogMsg &operator << (const signed short &t) { stream << t; return space(); }
    LogMsg &operator << (const unsigned short &t) { stream << t; return space(); }
    LogMsg &operator << (const signed int &t) { stream << t; return space(); }
    LogMsg &operator << (const unsigned int &t) { stream << t; return space(); }
    LogMsg &operator << (const signed long &t) { stream << t; return space(); }
    LogMsg &operator << (const unsigned long int &t) { stream << t; return space(); }
    LogMsg &operator << (const qint64 &t) { stream << t; return space(); }
    LogMsg &operator << (const quint64 &t) { stream << t; return space(); }
    LogMsg &operator << (const float &t) { stream << t; return space(); }
    LogMsg &operator << (const double &t) { stream << t; return space(); }
    //LogMsg &operator << (const bool &t) { if(t){stream << "true";} else {stream << "false";} return space(); }
    //LogMsg &operator << (const QByteArray &t) { stream << t; return space(); }
};


#endif // LOGCORE_H
