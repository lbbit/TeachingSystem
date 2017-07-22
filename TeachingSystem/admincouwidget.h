#ifndef ADMINCOUWIDGET_H
#define ADMINCOUWIDGET_H

#include <QWidget>
#include "dbconnection.h"
#include<QLabel>
#include<QLineEdit>
#include<QTableView>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSqlRelationalTableModel>
#include<QComboBox>
class AdminCouWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminCouWidget(QWidget *parent = 0);

signals:

public slots:
    void click_search();
    void click_submit();
    void click_cancel();
    void click_add();
    void click_delete();
    void change_combox();
private:
    QLabel *label_cid;
    QLineEdit *lineedit_cid;
    QPushButton *button_search;
    QTableView *table_cou;
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
    QSqlRelationalTableModel *model_cou;
    QLabel *label_currenttime;
    QComboBox *combobox_currenttime;
};

#endif // ADMINCOUWIDGET_H
