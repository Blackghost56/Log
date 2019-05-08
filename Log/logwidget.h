#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QDebug>
#include "logcore.h"
#include "logwidgetft.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::LogWidget *ui;

    LogWidgetFT *categoryTable;
    LogWidgetFT *groupTable;

public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();
    void add(const QString &str);

public slots:
    //void addData(const LogCore::LogData &data);
    void addString(const QString &str);
    void categoriesHasChanged(const QVector<QString> &categories, const QMap<QString, bool> categoriesState);
};

#endif // LOGWIDGET_H
