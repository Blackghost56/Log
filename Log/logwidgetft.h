#ifndef LOGWIDGETFT_H
#define LOGWIDGETFT_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class LogWidgetFT;
}

class LogWidgetFT : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidgetFT(const QString &title, QWidget *parent = nullptr);
    ~LogWidgetFT();
    void setPrefixState(bool state);
    void addRow(const QString &str, const bool state);
    void clear();
    void setTitle(const QString &title);
    QString getTitle();

private:
    Ui::LogWidgetFT *ui;

public slots:

private slots:
    void checkToggled(bool checked);
signals:
    void stateChanged(const QString &property, const bool state);
    void prefixStateChanged(bool state);
};

#endif // LOGWIDGETFT_H
