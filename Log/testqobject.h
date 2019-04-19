#ifndef TESTQOBJECT_H
#define TESTQOBJECT_H

#include <QObject>
#include "logcore.h"

class TestQObject : public QObject
{
    Q_OBJECT
public:
    explicit TestQObject(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TESTQOBJECT_H
