#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    //qRegisterMetaType<LogCore::LogData>("const LogCore::LogData &");

    //connect(LogCoreInstance.getLogHandlerPtr(), &LogHandler::serviceInformation, this, &LogWidget::addString);

    ui->TextEdit->setReadOnly(true);

    categoryTable = new LogWidgetFT(tr("Category"));
    connect(categoryTable, &LogWidgetFT::stateChanged, this, &LogWidget::stateChangedCategory);
    groupTable = new LogWidgetFT(tr("Group"));
    connect(groupTable, &LogWidgetFT::stateChanged, this, &LogWidget::stateChangedGroup);

    ui->Filter_Layout->addWidget(categoryTable);
    ui->Filter_Layout->addWidget(groupTable);


    categoryTable->addRow("Test 1", true);
    categoryTable->addRow("Test 2", false);

    groupTable->addRow("Test 1", true);
    groupTable->addRow("Test 2", false);

}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::add(const QString &str)
{
    ui->TextEdit->appendPlainText(str);
}

/*void LogWidget::addData(const LogCore::LogData &data)
{
    add(data.msg);
}*/

void LogWidget::addString(const QString &str)
{
    //qDebug() << "addString";
    add(str);
}

void LogWidget::categoriesHasChanged(const QVector<QString> &categories, const QMap<QString, bool> categoriesState)
{
    //qDebug() << categories;

}

void LogWidget::stateChangedCategory(const QString &property, const bool state)
{

}

void LogWidget::stateChangedGroup(const QString &property, const bool state)
{

}
