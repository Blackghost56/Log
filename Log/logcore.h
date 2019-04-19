#ifndef LOGCORE_H
#define LOGCORE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>

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


struct Context
{

};

#define FILE static_cast<const char *>(__FILE__)
#define LINE __LINE__
#define FUNC static_cast<const char *>(Q_FUNC_INFO)
#define LogDebug LogMsg(FILE, LINE, FUNC).Debug
#define LogInfo LogMsg(FILE, LINE, FUNC).Info

class LogMsg
{
private:
    QString msg;
    QString context;
    QTextStream stream;
public:
    LogMsg(const char *file, int line, const char *function);
    ~LogMsg();
    LogMsg &Debug();
    LogMsg &Info();

    /*LogMsg& operator << (const QString &str){
        msg.append(str);
        return *this;
    }*/

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
