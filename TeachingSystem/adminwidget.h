#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QTabWidget>
#include"admincouwidget.h"
#include"adminstuwidget.h"
#include"adminteawidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
class AdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(QString id,QWidget *parent = 0);

signals:

public slots:
    void click_logout();
private:
    QLabel *label_name;
    QPushButton *button_logout;
    QTabWidget *tabwidget_all;
    AdminCouWidget *acw;
    AdminStuWidget *asw;
    AdminTeaWidget *atw;
    QVBoxLayout *vlayout_all;
    QHBoxLayout *hlayout_top;
    QString id;
    void init_layout();
    void init_connect();
};

#endif // ADMINWIDGET_H
