#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QTabWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"stucouwidget.h"
#include"stupasswidget.h"
#include"stuscorewidget.h"
class StudentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StudentWidget(QString sid,QWidget *parent = 0);

signals:

public slots:
    void click_logout();
private:
    QLabel *label_sid;
    QPushButton *button_logout;
    QHBoxLayout *hlayout_top;
    QVBoxLayout *vlayout_all;
    QTabWidget *tabweight;
    StuCouWidget *scw;
    StuPassWidget *spw;
    StuScoreWidget *ssw;
    QString sid;
    void init_layout();
    void init_connect();
};

#endif // STUDENTWIDGET_H
