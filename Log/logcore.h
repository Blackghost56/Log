#ifndef LOGCORE_H
#define LOGCORE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>

class LogCore
{
public:
    enum LogGroup : int {Debug, Info};
    QMap<int, QString> LogGroupString = {{Debug, "Debug"}, {Info, "Info"}};

    struct LogData
    {
        LogData () : category("Default"), ptr(nullptr) {}
        QString msg;
        QString context;
        LogGroup group;
        QString category;
        const QObject *ptr;
    };

private:
    //LogData data;
    QMultiMap<QString, const QObject *> categories;
    QMap<const QObject *, QString> catptr;

    bool ObjectIsBinded(const QObject *ptr, QString &category);

    LogCore();
    LogCore(const LogCore&) = delete;
    LogCore& operator = (LogCore&) = delete;
    //~LogCore();
public:
    static LogCore &getInstance();

    //void add(const QString &str);
    void addData(const LogData &data);

    //void addCategory(const QString &category);
    void bindQObjectWithCategory(const QString &category, const QObject *ptr);

};


/*#define LogAddCategory(category) \
                LogCore::getInstance().addCategory(category);*/
#define LogBindQObject(category) \
                LogCore::getInstance().bindQObjectWithCategory(category, this);


#define FILE static_cast<const char *>(__FILE__)
#define LINE __LINE__
#define FUNC static_cast<const char *>(Q_FUNC_INFO)

#define LogDebug LogMsg(FILE, LINE, FUNC).Debug
#define LogInfo LogMsg(FILE, LINE, FUNC).Info

#define LogDebugQOC LogMsg(FILE, LINE, FUNC, this).Debug
#define LogInfoQOC LogMsg(FILE, LINE, FUNC, this).Info

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


    LogMsg &operator << (const QString &str) { stream << str; return *this; }
    LogMsg &operator << (const int &t) { stream << t; return *this; }

    /*
    inline QDebug &maybeSpace() { if (stream->space) stream->ts << ' '; return *this; }

    inline QDebug &operator<<(QChar t) { putUcs4(t.unicode()); return maybeSpace(); }
    inline QDebug &operator<<(bool t) { stream->ts << (t ? "true" : "false"); return maybeSpace(); }
    inline QDebug &operator<<(char t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(signed short t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(unsigned short t) { stream->ts << t; return maybeSpace(); }
#ifdef Q_COMPILER_UNICODE_STRINGS
    inline QDebug &operator<<(char16_t t) { return *this << QChar(ushort(t)); }
    inline QDebug &operator<<(char32_t t) { putUcs4(t); return maybeSpace(); }
#endif
    inline QDebug &operator<<(signed int t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(unsigned int t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(signed long t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(unsigned long t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(qint64 t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(quint64 t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(float t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(double t) { stream->ts << t; return maybeSpace(); }
    inline QDebug &operator<<(const char* t) { stream->ts << QString::fromUtf8(t); return maybeSpace(); }
#if QT_STRINGVIEW_LEVEL < 2
    inline QDebug &operator<<(const QString & t) { putString(t.constData(), uint(t.length())); return maybeSpace(); }
    inline QDebug &operator<<(const QStringRef & t) { putString(t.constData(), uint(t.length())); return maybeSpace(); }
#endif
    inline QDebug &operator<<(QStringView s) { putString(s.data(), size_t(s.size())); return maybeSpace(); }
    inline QDebug &operator<<(QLatin1String t) { putByteArray(t.latin1(), t.size(), ContainsLatin1); return maybeSpace(); }
    inline QDebug &operator<<(const QByteArray & t) { putByteArray(t.constData(), t.size(), ContainsBinary); return maybeSpace(); }
    inline QDebug &operator<<(const void * t) { stream->ts << t; return maybeSpace(); }
#ifdef Q_COMPILER_NULLPTR
    inline QDebug &operator<<(std::nullptr_t) { stream->ts << "(nullptr)"; return maybeSpace(); }
#endif
    inline QDebug &operator<<(QTextStreamFunction f) {
        stream->ts << f;
        return *this;
    }

    inline QDebug &operator<<(QTextStreamManipulator m)
    { stream->ts << m; return *this; }
    */

};


#endif // LOGCORE_H
