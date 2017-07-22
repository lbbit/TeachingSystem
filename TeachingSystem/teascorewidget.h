#ifndef TEASCOREWIDGET_H
#define TEASCOREWIDGET_H

#include <QWidget>
#include"dbconnection.h"
#include<QPushButton>
#include<QTableView>
#include<QSqlRelationalTableModel>
#include<QVBoxLayout>
#include<QHBoxLayout>
class TeaScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeaScoreWidget(QString tid,QWidget *parent = 0);

signals:

public slots:
    void click_submit();
    void click_cancel();
private:
    QPushButton *button_submit;
    QPushButton *button_cancel;
    QTableView *table_score;
    QSqlRelationalTableModel *model_score;
    QHBoxLayout *hlayout_all;
    QVBoxLayout *vlayout_buttons;
    QString tID;
    void init_layout();
    void init_connect();
    void init_data();
};

#endif // TEASCOREWIDGET_H
