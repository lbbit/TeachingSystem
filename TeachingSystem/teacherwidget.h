#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QTabWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"teapasswidget.h"
#include"teascorewidget.h"
class TeacherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeacherWidget(QString tid,QWidget *parent = 0);

signals:

public slots:
    void click_logout();
private:
    QLabel *label_tid;
    QPushButton *button_logout;
    QHBoxLayout *hlayout_top;
    QVBoxLayout *vlayout_all;
    QTabWidget *tabweight;
    TeaPassWidget *tpw;
    TeaScoreWidget *tsw;
    QString tid;
    void init_layout();
    void init_connect();
};

#endif // TEACHERWIDGET_H
