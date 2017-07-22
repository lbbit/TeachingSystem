#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QStackedLayout>
#include"loginwidget.h"
#include"teacherwidget.h"
#include"studentwidget.h"
#include"adminwidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void login(int index,QString id);
private:
    QStackedLayout *stackw;
    AdminWidget *aw;
    TeacherWidget *tw;
    LoginWidget *lw;
    StudentWidget *stuw;
};

#endif // MAINWIDGET_H
