#include "teacherwidget.h"

TeacherWidget::TeacherWidget(QString tid,QWidget *parent) : QWidget(parent)
{
    this->tid=tid;
    init_layout();
    init_connect();
}
void TeacherWidget::init_layout()
{
    label_tid=new QLabel("教师编号"+tid,this);
    button_logout=new QPushButton("退出",this);
    button_logout->setVisible(false);
    tabweight=new QTabWidget(this);
    tsw=new TeaScoreWidget(tid,this);
    tpw=new TeaPassWidget(tid,this);
    tabweight->addTab(tsw,"成绩管理");
    tabweight->addTab(tpw,"修改密码");
    hlayout_top=new QHBoxLayout();
    vlayout_all=new QVBoxLayout();
    hlayout_top->addWidget(label_tid);
    hlayout_top->addStretch();
    hlayout_top->addWidget(button_logout);
    vlayout_all->addLayout(hlayout_top);
    vlayout_all->addWidget(tabweight);
    this->setLayout(vlayout_all);
}
void TeacherWidget::init_connect()
{
    connect(button_logout,&QPushButton::clicked,this,&TeacherWidget::click_logout);
}

void TeacherWidget::click_logout()
{
    this->close();
}
