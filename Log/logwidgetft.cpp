#include "logwidgetft.h"
#include "ui_logwidgetft.h"

LogWidgetFT::LogWidgetFT(const QString &title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidgetFT)
{
    ui->setupUi(this);

    ui->groupBox->setTitle(title);

    ui->table->setColumnCount(2);
    ui->table->verticalHeader()->setVisible(false);
    //ui->table->horizontalHeader()->setVisible(false);
    ui->table->setHorizontalHeaderLabels(QStringList() << tr("Filter") << tr("Enable"));
    //ui->table->setColumnWidth(1, 50);
    connect(ui->showPrefix_checkBox, &QCheckBox::toggled, this, &LogWidgetFT::prefixStateChanged);
}

LogWidgetFT::~LogWidgetFT()
{
    delete ui;
}

void LogWidgetFT::setPrefixState(bool state)
{
    ui->showPrefix_checkBox->setChecked(state);
}

void LogWidgetFT::addRow(const QString &str, const bool state)
{
    //qDebug() << str << " " << state;

    int rowCount = ui->table->rowCount();
    ui->table->setRowCount(ui->table->rowCount() + 1);

    QTableWidgetItem *itemName = new QTableWidgetItem(str);
    itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
    ui->table->setItem(rowCount, 0, itemName);

    QCheckBox *itemState = new QCheckBox();
    connect(itemState, &QCheckBox::toggled, this, &LogWidgetFT::checkToggled);
    //QWidget *widget = new QWidget;                    // very bad practice
    //QHBoxLayout *hlw = new QHBoxLayout;
    //widget->setLayout(hlw);
    //hlw->setMargin(0);
    //hlw->addWidget(itemState, 0, Qt::AlignCenter);
    itemState->setChecked(state);
    ui->table->setCellWidget(rowCount, 1, itemState);

    ui->table->resizeColumnsToContents();
    //ui->table->resizeColumnToContents(0);


}

void LogWidgetFT::clear()
{
     ui->table->clear();
     ui->table->setRowCount(0);
}

void LogWidgetFT::setTitle(const QString &title)
{
    ui->groupBox->setTitle(title);
}

QString LogWidgetFT::getTitle()
{
    return ui->groupBox->title();
}

void LogWidgetFT::checkToggled(bool checked)
{
    int colum = ui->table->currentColumn();
    int row = ui->table->currentRow();

    //qDebug() << "colum: " << colum << "   row: " <<  row;

    if (row >= 0 && colum >= 0)
    {
        //qDebug() << ui->table->item(row, 0)->text() << checked;
        emit stateChanged(ui->table->item(row, 0)->text(), checked);
    }

}
