#include "stucouwidget.h"
#include<QHeaderView>
#include"dbconnection.h"
#include<QMessageBox>
StuCouWidget::StuCouWidget(QString id,QWidget *parent) : QWidget(parent)
{
    sid=id;
    init_layout();
    init_connect();
    init_data();
}

void StuCouWidget::click_cancel()
{
    int indexrow=table_course->currentRow();
    if(indexrow==-1)
    {

    }
    else
    {
        if(table_course->item(indexrow,2)->text()=="可选")
        {

        }
        else
        {
            int ok = QMessageBox::warning(this,tr("退选!"),tr("你确定退选该课程吗？"),
                                 QMessageBox::Yes,QMessageBox::No);
            if(ok == QMessageBox::No)
            {
               //如果不删除
            }
            else
            {
                QString indexcid=table_course->item(indexrow,0)->text();
                QSqlQuery sqlquery;
                QString deletesql="delete from sc where cID=? and sID=?";
                sqlquery.prepare(deletesql);
                sqlquery.bindValue(0,indexcid);
                sqlquery.bindValue(1,sid);
                if(!sqlquery.exec())
                {
                    qDebug()<<sqlquery.lastError();
                }
                else
                {
                    init_data();
                }
            }


        }
    }
}
void StuCouWidget::click_select()
{
    int indexrow=table_course->currentRow();
    if(indexrow==-1)
    {

    }
    else
    {
        if(table_course->item(indexrow,2)->text()=="已选")
        {

        }
        else
        {
            int ok = QMessageBox::warning(this,tr("选课!"),tr("你确定选修该课程吗？"),
                                 QMessageBox::Yes,QMessageBox::No);
            if(ok == QMessageBox::No)
            {
               //如果不
            }
            else
            {
                QString indexcid=table_course->item(indexrow,0)->text();
                QSqlQuery sqlquery;
                QString insertsql="insert into sc(cID,sID) values(?,?)";
                sqlquery.prepare(insertsql);
                sqlquery.bindValue(0,indexcid);
                sqlquery.bindValue(1,sid);
                if(!sqlquery.exec())
                {
                    qDebug()<<sqlquery.lastError();
                }
                else
                {
                    init_data();
                }
            }


        }
    }
}
void StuCouWidget::init_layout()
{
    button_cancel=new QPushButton("退选",this);
    button_select=new QPushButton("选课",this);
    table_course=new QTableWidget(this);
    table_course->setColumnCount(3);
    table_course->setMinimumSize(450,300);
    QStringList table_header;   //表头
    table_header<<"课程号"<<"课程名称"<<"状态";
    table_course->setHorizontalHeaderLabels(table_header);
    table_course->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_course->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_course->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置禁止编辑
    table_course->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    vlayout_right=new QVBoxLayout();
    hlayout_all=new QHBoxLayout();
    vlayout_right->addWidget(button_cancel);
    vlayout_right->addWidget(button_select);
    hlayout_all->addWidget(table_course);
    hlayout_all->addLayout(vlayout_right);
    this->setLayout(hlayout_all);
}
void StuCouWidget::init_connect()
{
    connect(button_cancel,&QPushButton::clicked,this,&StuCouWidget::click_cancel);
    connect(button_select,&QPushButton::clicked,this,&StuCouWidget::click_select);
}
void StuCouWidget::init_data()
{
    table_course->clearContents();
    int rowindex=0;
    QSqlQuery sqlquery;
    QString selectsql="select course.cID,course.cname from course where course.cID in (select cID from sc where sID=?)";
    sqlquery.prepare(selectsql);
    sqlquery.bindValue(0,sid);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        table_course->setRowCount(rowindex);
        while(sqlquery.next())
        {
            //将查询的内容写入表格
            table_course->setRowCount(++rowindex);
            for(int col=0;col<2;col++)
            {
                table_course->setItem(rowindex-1,col,new QTableWidgetItem(sqlquery.value(col).toString()));
            }
            table_course->setItem(rowindex-1,2,new QTableWidgetItem("已选"));
        }
    }
    int stugrade=1;//学生年级
    int nowtime=1;//当前学期
    int stutime;//学生学期
    selectsql="select ntime from nowtime where nID=1";
    //查询所有记录
    sqlquery.prepare(selectsql);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        while(sqlquery.next())
        {
           nowtime=sqlquery.value(0).toInt();
        }
    }
    selectsql="select grade from student where sID=?";
    sqlquery.bindValue(0,sid);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        while(sqlquery.next())
        {
           stugrade=sqlquery.value(0).toInt();
        }
    }
    stutime=2*stugrade-(2-nowtime);
    selectsql="select course.cID,course.cname from course where time=? and course.cID not in (select cID from sc where sID=?)";
    sqlquery.prepare(selectsql);
    sqlquery.bindValue(0,stutime);
    sqlquery.bindValue(1,sid);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        while(sqlquery.next())
        {
            //将查询的内容写入表格
            table_course->setRowCount(++rowindex);
            for(int col=0;col<2;col++)
            {
                table_course->setItem(rowindex-1,col,new QTableWidgetItem(sqlquery.value(col).toString()));
            }
            table_course->setItem(rowindex-1,2,new QTableWidgetItem("可选"));
        }
    }
}
