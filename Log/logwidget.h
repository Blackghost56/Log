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
private slots:
    void on_time_checkBox_toggled(bool checked);
    void on_context_checkBox_toggled(bool checked);
    void category_prefixStateChanged_toggled(bool checked);
    void group_prefixStateChanged_toggled(bool checked);
    void categoryTable_stateChanged(const QString &property, const bool state);
    void groupTable_stateChanged(const QString &property, const bool state);
};

#endif // LOGWIDGET_H
