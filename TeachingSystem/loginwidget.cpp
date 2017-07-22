#include "loginwidget.h"
#include "dbconnection.h"
#include<QMessageBox>
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    init_layout();
    init_connect();
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::init_connect()
{
    connect(button_login,&QPushButton::clicked,this,&LoginWidget::login_action);
    connect(button_close,&QPushButton::clicked,this,&LoginWidget::quit_action);
}

void LoginWidget::init_layout()
{
    label_name=new QLabel("用户名");
    label_name->setParent(this);
    label_passwd=new QLabel("密码");
    label_passwd->setParent(this);
    lineedit_name=new QLineEdit(this);
    lineedit_name->setPlaceholderText("用户ID");  //编辑框的提示文字
    lineedit_passwd=new QLineEdit(this);
    lineedit_passwd->setEchoMode(QLineEdit::Password);  //密码框显示模式
    radio_manager=new QRadioButton("管理员",this);
    radio_teacher=new QRadioButton("教师",this);
    radio_student=new QRadioButton("学生",this);
    radio_manager->setChecked(true);
    button_login=new QPushButton("登录");
    button_login->setParent(this);
    button_close=new QPushButton("退出");
    button_close->setParent(this);
    //布局
    formlayout_loginform=new QFormLayout();
    hlayout_radio=new QHBoxLayout();
    formlayout_loginform->addRow(label_name,lineedit_name);
    formlayout_loginform->addRow(label_passwd,lineedit_passwd);
    hlayout_radio->addWidget(radio_manager);
    hlayout_radio->addWidget(radio_teacher);
    hlayout_radio->addWidget(radio_student);
    formlayout_loginform->addRow(hlayout_radio);
    formlayout_loginform->addRow(button_login,button_close);
    this->setLayout(formlayout_loginform);
}

void LoginWidget::login_action()
{
    if(lineedit_name->text().isEmpty()||lineedit_passwd->text().isEmpty())
    {
        //提示没输入
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("用户名密码不能为空！"));
    }
    else
    {
        QString indexname=lineedit_name->text();
        QString indexpasswd=lineedit_passwd->text();
        QSqlQuery sql_query;
        QString checksql="";
        if(radio_manager->isChecked())
        {
            checksql="select * from manager where mID=? and passwd=?";
            sql_query.prepare(checksql);
            sql_query.bindValue(0,indexname);
            sql_query.bindValue(1,indexpasswd);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                if(sql_query.next())
                {
                    emit display(1,indexname);
                }
                else
                {
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("账号密码错误！"));
                }
            }
        }
        else if(radio_teacher->isChecked())
        {
            checksql="select * from teacher where tID=? and passwd=?";
            sql_query.prepare(checksql);
            sql_query.bindValue(0,indexname);
            sql_query.bindValue(1,indexpasswd);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                if(sql_query.next())
                {
                    emit display(2,indexname);
                }
                else
                {
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("账号密码错误！"));
                }
            }
        }
        else if(radio_student->isChecked())
        {
            checksql="select * from student where sID=? and passwd=?";
            sql_query.prepare(checksql);
            sql_query.bindValue(0,indexname);
            sql_query.bindValue(1,indexpasswd);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                if(sql_query.next())
                {
                    emit display(3,indexname);
                }
                else
                {
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("账号密码错误！"));
                }
            }
        }
    }
}

void LoginWidget::quit_action()
{
    this->close();
}
