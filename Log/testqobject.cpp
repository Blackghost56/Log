#include "testqobject.h"

TestQObject::TestQObject(QObject *parent) : QObject(parent)
{
    LogBindQObject("d");

    LogInfoQOC("Category test Qobject") << "Test QObject with category";

    LogInfoQOC() << "Test QObject ";
}
