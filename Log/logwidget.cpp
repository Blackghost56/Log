#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    qRegisterMetaType<LogCore::LogData>("const LogCore::LogData &");

}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::add(const QString &str)
{
    ui->plainTextEdit->appendPlainText(str);
}

void LogWidget::addData(const LogCore::LogData &data)
{
    add(data.msg);
}

void LogWidget::addString(QString str)
{
    qDebug() << "addString";
    add(str);
}
