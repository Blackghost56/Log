#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QObject>
#include <QThread>
#include "logcore.h"

class TestThread : public QThread
{
public:
    TestThread(QString name, QObject *obj = nullptr);
    void run() override{
        int i = 0;
        while (i < 1000) {
            //LogInfo() << "Test Thread";
            LogInfoQOC() << i;
            i++;
        }
    }
};


#endif // TESTTHREAD_H
