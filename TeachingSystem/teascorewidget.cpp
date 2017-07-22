#include "teascorewidget.h"
#include<QMessageBox>
#include<QHeaderView>
TeaScoreWidget::TeaScoreWidget(QString tid,QWidget *parent) : QWidget(parent)
{
    tID=tid;
    init_layout();
    init_connect();
    init_data();
}
void TeaScoreWidget::init_layout()
{
    button_submit=new QPushButton("提交修改",this);
    button_cancel=new QPushButton("撤销修改",this);
    table_score=new QTableView(this);
    table_score->setMinimumSize(450,300);
    table_score->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_score->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_score->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    table_score->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //列宽度自适应
    vlayout_buttons=new QVBoxLayout();
    vlayout_buttons->addStretch();
    vlayout_buttons->addWidget(button_submit);
    vlayout_buttons->addWidget(button_cancel);
    hlayout_all=new QHBoxLayout();
    hlayout_all->addWidget(table_score);
    hlayout_all->addLayout(vlayout_buttons);
    this->setLayout(hlayout_all);
}
void TeaScoreWidget::init_connect()
{
    connect(button_submit,&QPushButton::clicked,this,&TeaScoreWidget::click_submit);
    connect(button_cancel,&QPushButton::clicked,this,&TeaScoreWidget::click_cancel);
}
void TeaScoreWidget::init_data()
{
    model_score=new QSqlRelationalTableModel(this);
    model_score->setTable("sc");
    model_score->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_score->select();
    model_score->setHeaderData(0, Qt::Horizontal, tr("课程名称"));
    model_score->setHeaderData(1, Qt::Horizontal, tr("学号"));
    model_score->setHeaderData(2, Qt::Horizontal, tr("成绩"));
    QStringList indexcoueses;
    QSqlQuery sqlquery;
    QString selectsql="select cID from course where tID=?";
    sqlquery.prepare(selectsql);
    sqlquery.bindValue(0,tID);
    if(!sqlquery.exec())
    {
        qDebug()<<sqlquery.lastError();
    }
    else
    {
        while (sqlquery.next())
        {
            indexcoueses.append(sqlquery.value(0).toString());
        }
    }
    QString filterstr="";
    int i;
    if(indexcoueses.length()<=0)
    {
        return ;
    }
    for(i=0;i<indexcoueses.length()-1;i++)
    {
        filterstr=filterstr+"cID='"+indexcoueses[i]+"' or ";
    }
    filterstr=filterstr+"cID='"+indexcoueses[i]+"'";
    qDebug()<<filterstr;
    QByteArray ba = filterstr.toLatin1();
    model_score->setFilter(QObject::tr(ba.data()));
    model_score->select();
    //model_score->setRelation(0,QSqlRelation("course","cID","cname"));
    table_score->setModel(model_score);
}
void TeaScoreWidget::click_cancel()
{
    model_score->revertAll();
}
void TeaScoreWidget::click_submit()
{
    model_score->database().transaction(); //开始事务操作
    if (model_score->submitAll()) {
        model_score->database().commit(); //提交
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("修改成功！"));
    }
    else
    {
        model_score->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_score->lastError().text()));
    }
}
