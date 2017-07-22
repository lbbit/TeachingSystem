#ifndef STUCOUWIDGET_H
#define STUCOUWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTableWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
class StuCouWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StuCouWidget(QString id,QWidget *parent = 0);

signals:

public slots:
    void click_select();
    void click_cancel();
private:
    QTableWidget *table_course;
    QPushButton *button_cancel;
    QPushButton *button_select;
    QVBoxLayout *vlayout_right;
    QHBoxLayout *hlayout_all;
    QString sid;
    void init_layout();
    void init_data();
    void init_connect();
};

#endif // STUCOUWIDGET_H
