#include "stuscorewidget.h"
#include<QHeaderView>
StuScoreWidget::StuScoreWidget(QString id,QWidget *parent) : QWidget(parent)
{
    sid=id;
    table_score=new QTableWidget(this);
    table_score->setColumnCount(3);
    table_score->setMinimumSize(450,300);
    QStringList table_header;   //表头
    table_header<<"课程号"<<"课程名称"<<"成绩";
    table_score->setHorizontalHeaderLabels(table_header);
    table_score->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_score->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_score->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置禁止编辑
    table_score->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    init_data();
}
void StuScoreWidget::init_data()
{
    QSqlQuery sqlquery;
    QString selectsql="select course.cID,course.cname,sc.score from course,sc where course.cID=sc.cID and sc.sID=?";
    sqlquery.prepare(selectsql);
    sqlquery.bindValue(0,sid);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        int rowindex=0;
        table_score->setRowCount(rowindex);
        while(sqlquery.next())
        {
            //将查询的内容写入表格
            table_score->setRowCount(++rowindex);
            for(int col=0;col<3;col++)
            {
                table_score->setItem(rowindex-1,col,new QTableWidgetItem(sqlquery.value(col).toString()));
            }
            if(sqlquery.value(2).toString()=="0")
            {
                table_score->setItem(rowindex-1,2,new QTableWidgetItem("null"));
            }

        }
    }
}
