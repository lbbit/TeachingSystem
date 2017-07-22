#include "adminwidget.h"
#include"loginwidget.h"
AdminWidget::AdminWidget(QString id,QWidget *parent) : QWidget(parent)
{
    this->id=id;
    init_layout();
    init_connect();
}
void AdminWidget::init_layout()
{
    label_name=new QLabel(this);
    label_name->setText("管理员："+id);
    button_logout=new QPushButton("退出",this);
    button_logout->setVisible(false);
    tabwidget_all=new QTabWidget(this);
    atw=new AdminTeaWidget(this);
    asw=new AdminStuWidget(this);
    acw=new AdminCouWidget(this);
    tabwidget_all->addTab(atw,"教师管理");
    tabwidget_all->addTab(asw,"学生管理");
    tabwidget_all->addTab(acw,"课程管理");
    hlayout_top=new QHBoxLayout();
    hlayout_top->addWidget(label_name);
    hlayout_top->addStretch();
    hlayout_top->addWidget(button_logout);
    vlayout_all=new QVBoxLayout();
    vlayout_all->addLayout(hlayout_top);
    vlayout_all->addWidget(tabwidget_all);
    this->setLayout(vlayout_all);
}
void AdminWidget::init_connect()
{
    connect(button_logout,&QPushButton::clicked,this,&AdminWidget::click_logout);
}
void AdminWidget::click_logout()
{
    this->close();
}
