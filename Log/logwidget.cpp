#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    //qRegisterMetaType<LogCore::LogData>("const LogCore::LogData &");
    qRegisterMetaType<QVector<QString>>("const QVector<QString> &");

    //connect(LogCoreInstance.getLogHandlerPtr(), &LogHandler::serviceInformation, this, &LogWidget::addString);

    ui->TextEdit->setReadOnly(true);

    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();

    categoryTable = new LogWidgetFT(tr("Category"));
    ui->Filter_Layout->addWidget(categoryTable);
    categoryTable->setPrefixState(filterState.categoriesPrefixVisible);
    connect(categoryTable, &LogWidgetFT::stateChanged, this, &LogWidget::categoryTable_stateChanged);
    connect(categoryTable, &LogWidgetFT::prefixStateChanged, this, &LogWidget::category_prefixStateChanged_toggled);

    groupTable = new LogWidgetFT(tr("Group"));
    ui->Filter_Layout->addWidget(groupTable);
    groupTable->setPrefixState(filterState.groupPrefixVisible);
    connect(groupTable, &LogWidgetFT::stateChanged, this, &LogWidget::groupTable_stateChanged);
    connect(groupTable, &LogWidgetFT::prefixStateChanged, this, &LogWidget::group_prefixStateChanged_toggled);

    /*ui->Filter_Layout->addWidget(categoryTable);
    ui->Filter_Layout->addWidget(groupTable);


    categoryTable->addRow("Test 1", true);
    categoryTable->addRow("Test 2", false);

    groupTable->addRow("Test 1", true);
    groupTable->addRow("Test 2", false);*/


    QString buf;

    for (int i = 0; i < LogCore::LogGroup::last; i++)
    {
        //qDebug() << inst.LogGroupToString(i);
        buf = logCoreRef.LogGroupToString(i);
        groupTable->addRow(buf, filterState.groupState.value(buf));
    }

    ui->time_checkBox->setChecked(filterState.timePrefixVisible);
    ui->context_checkBox->setChecked(filterState.contextPrefixVisible);

    //ui->Filter_Layout->addStretch(1);
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
    categoryTable->clear();
    for (auto i : categories)
    {
        categoryTable->addRow(i, categoriesState.value(i));
    }
}

void LogWidget::on_time_checkBox_toggled(bool checked)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.timePrefixVisible = checked;
    logCoreRef.setFilterState(filterState);
}

void LogWidget::on_context_checkBox_toggled(bool checked)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.contextPrefixVisible = checked;
    logCoreRef.setFilterState(filterState);
}

void LogWidget::category_prefixStateChanged_toggled(bool checked)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.categoriesPrefixVisible = checked;
    logCoreRef.setFilterState(filterState);
}

void LogWidget::group_prefixStateChanged_toggled(bool checked)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.groupPrefixVisible = checked;
    logCoreRef.setFilterState(filterState);
}

void LogWidget::categoryTable_stateChanged(const QString &property, const bool state)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.categoriesState[property] = state;
    logCoreRef.setFilterState(filterState);
}

void LogWidget::groupTable_stateChanged(const QString &property, const bool state)
{
    LogCore & logCoreRef = LogCoreInstance;
    LogCore::Filter filterState = logCoreRef.getFilterState();
    filterState.groupState[property] = state;
    logCoreRef.setFilterState(filterState);
}
