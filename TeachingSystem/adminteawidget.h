#ifndef ADMINTEAWIDGET_H
#define ADMINTEAWIDGET_H

#include <QWidget>
#include "dbconnection.h"
#include<QLabel>
#include<QLineEdit>
#include<QTableView>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSqlTableModel>
class AdminTeaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminTeaWidget(QWidget *parent = 0);

signals:

public slots:
    void click_search();
    void click_submit();
    void click_cancel();
    void click_add();
    void click_delete();
private:
    QLabel *label_tid;
    QLineEdit *lineedit_tid;
    QPushButton *button_search;
    QTableView *table_tea;
    QPushButton *button_submit;
    QPushButton *button_cancel;
    QPushButton *button_add;
    QPushButton *button_delete;
    QHBoxLayout *hlayout_search;
    QVBoxLayout *vlayout_left;
    QVBoxLayout *vlayout_rightbuttons;
    QHBoxLayout *hlayout_all;
    void init_layout();
    void init_connect();
    void init_data();
    QSqlTableModel *model_tea;
};

#endif // ADMINTEAWIDGET_H
