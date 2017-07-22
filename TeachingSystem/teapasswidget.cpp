#include "teapasswidget.h"
#include<QMessageBox>
#include"dbconnection.h"
TeaPassWidget::TeaPassWidget(QString tid,QWidget *parent) : QWidget(parent)
{
    teaID=tid;
    init_layout();
    init_connect();

}
void TeaPassWidget::init_layout()
{
    label_oldpass=new QLabel("旧密码",this);
    label_newpass=new QLabel("新密码",this);
    label_repass=new QLabel("重复密码",this);
    lineedit_oldpass=new QLineEdit(this);
    lineedit_newpass=new QLineEdit(this);
    lineedit_repass=new QLineEdit(this);
    lineedit_newpass->setEchoMode(QLineEdit::Password);  //密码框显示模式
    lineedit_oldpass->setEchoMode(QLineEdit::Password);  //密码框显示模式
    lineedit_repass->setEchoMode(QLineEdit::Password);  //密码框显示模式
    button_confirm=new QPushButton("确认修改",this);
    button_reset=new QPushButton("重新输入",this);
    formlayout_all=new QFormLayout();
    formlayout_all->addRow(label_oldpass,lineedit_oldpass);
    formlayout_all->addRow(label_newpass,lineedit_newpass);
    formlayout_all->addRow(label_repass,lineedit_repass);
    formlayout_all->addRow(button_confirm,button_reset);
    this->setLayout(formlayout_all);
}
void TeaPassWidget::init_connect()
{
    connect(button_confirm,&QPushButton::clicked,this,&TeaPassWidget::click_confirm);
    connect(button_reset,&QPushButton::clicked,this,&TeaPassWidget::click_reset);
}
void TeaPassWidget::click_confirm()
{
    if(lineedit_newpass->text().isEmpty()||lineedit_oldpass->text().isEmpty()||lineedit_repass->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("密码不能为空！"));
    }
    else if(lineedit_newpass->text()!=lineedit_repass->text())
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("重复密码不相同，请检查！"));
    }
    else
    {
        QString indexoldpass=lineedit_oldpass->text();
        QString indexnewpass=lineedit_newpass->text();
        QSqlQuery sql_query;
        QString selectsql="";
        selectsql="select * from teacher where tID=? and passwd=?";
        sql_query.prepare(selectsql);
        sql_query.bindValue(0,teaID);
        sql_query.bindValue(1,indexoldpass);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError().text();
            return;
        }
        else
        {
            if(sql_query.next())
            {
                //旧密码输入正确，修改密码
                QSqlQuery sql_update;
                QString updatesql="update teacher set passwd=? where tID=?";
                sql_update.prepare(updatesql);
                sql_update.bindValue(0,indexnewpass);
                sql_update.bindValue(1,teaID);
                if(!sql_update.exec())
                {
                    qDebug()<<sql_update.lastError().text();
                    return ;
                }
                else
                {
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("密码修改成功！"));
                    click_reset();
                }
            }
            else
            {
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("原密码错误！"));
            }
        }
    }


}
void TeaPassWidget::click_reset()
{
    lineedit_newpass->clear();
    lineedit_oldpass->clear();
    lineedit_repass->clear();
}
