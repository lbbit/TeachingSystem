#include "studentwidget.h"

StudentWidget::StudentWidget(QString id,QWidget *parent) : QWidget(parent)
{
    this->sid=id;
    init_layout();
    init_connect();
}
void StudentWidget::init_layout()
{
    label_sid=new QLabel("学号"+sid,this);
    button_logout=new QPushButton("退出",this);
    button_logout->setVisible(false);
    tabweight=new QTabWidget(this);
    ssw=new StuScoreWidget(sid,this);
    spw=new StuPassWidget(sid,this);
    scw=new StuCouWidget(sid,this);
    tabweight->addTab(ssw,"成绩查询");
    tabweight->addTab(scw,"选课管理");
    tabweight->addTab(spw,"修改密码");
    hlayout_top=new QHBoxLayout();
    vlayout_all=new QVBoxLayout();
    hlayout_top->addWidget(label_sid);
    hlayout_top->addStretch();
    hlayout_top->addWidget(button_logout);
    vlayout_all->addLayout(hlayout_top);
    vlayout_all->addWidget(tabweight);
    this->setLayout(vlayout_all);
}
void StudentWidget::init_connect()
{
    connect(button_logout,&QPushButton::clicked,this,&StudentWidget::click_logout);
}

void StudentWidget::click_logout()
{
    this->close();
}
