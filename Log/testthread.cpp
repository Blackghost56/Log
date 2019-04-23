#include "testthread.h"

TestThread::TestThread(QString name, QObject *obj) : QThread(obj)
{
    LogBindQObject(name)
}
