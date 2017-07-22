#include "admincouwidget.h"
#include<QHeaderView>
#include<QMessageBox>
#include<QSqlRelation>
AdminCouWidget::AdminCouWidget(QWidget *parent) : QWidget(parent)
{
    init_layout();
    init_connect();
    init_data();
}

void AdminCouWidget::init_layout()
{
    label_cid=new QLabel("课程号");
    label_cid->setParent(this);
    label_currenttime=new QLabel("设置当前学期");
    label_currenttime->setParent(this);
    lineedit_cid=new QLineEdit(this);
    button_search=new QPushButton("搜索",this);
    button_submit=new QPushButton("提交修改",this);
    button_cancel=new QPushButton("撤销修改",this);
    button_add=new QPushButton("添加记录",this);
    button_delete=new QPushButton("删除记录",this);
    combobox_currenttime=new QComboBox(this);
    combobox_currenttime->addItem("1");
    combobox_currenttime->addItem("2");
    hlayout_search=new QHBoxLayout();
    hlayout_search->addWidget(label_cid);
    hlayout_search->addWidget(lineedit_cid);
    hlayout_search->addWidget(button_search);
    hlayout_search->addWidget(label_currenttime);
    hlayout_search->addWidget(combobox_currenttime);
    hlayout_search->addStretch();
    vlayout_left=new QVBoxLayout();
    vlayout_left->addLayout(hlayout_search);
    table_cou=new QTableView(this);
    vlayout_left->addWidget(table_cou);
    table_cou->setMinimumSize(450,300);
    table_cou->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_cou->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_cou->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    table_cou->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //列宽度自适应
    vlayout_rightbuttons=new QVBoxLayout();
    vlayout_rightbuttons->addStretch();
    vlayout_rightbuttons->addWidget(button_submit);
    vlayout_rightbuttons->addWidget(button_cancel);
    vlayout_rightbuttons->addWidget(button_add);
    vlayout_rightbuttons->addWidget(button_delete);
    hlayout_all=new QHBoxLayout();
    hlayout_all->addLayout(vlayout_left);
    hlayout_all->addLayout(vlayout_rightbuttons);
    this->setLayout(hlayout_all);
}

void AdminCouWidget::init_connect()
{
    connect(button_search,&QPushButton::clicked,this,&AdminCouWidget::click_search);
    connect(button_submit,&QPushButton::clicked,this,&AdminCouWidget::click_submit);
    connect(button_cancel,&QPushButton::clicked,this,&AdminCouWidget::click_cancel);
    connect(button_add,&QPushButton::clicked,this,&AdminCouWidget::click_add);
    connect(button_delete,&QPushButton::clicked,this,&AdminCouWidget::click_delete);
    connect(combobox_currenttime,SIGNAL(currentIndexChanged(int)),this,SLOT(change_combox()));
}

void AdminCouWidget::init_data()
{
    QSqlQuery sql_query;
    QString selectsql="select ntime from nowtime where nID=1";
    //查询所有记录
    sql_query.prepare(selectsql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        //qDebug()<<"select success!";
        int indextime = 1;
        while(sql_query.next())
        {
           indextime=sql_query.value(0).toInt();
        }
        if(indextime==1)
        {
            combobox_currenttime->setCurrentIndex(0);
        }
        else
        {
            combobox_currenttime->setCurrentIndex(1);
        }
    }
    model_cou=new QSqlRelationalTableModel(this);
    model_cou->setTable("course");
    model_cou->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_cou->setRelation(2,QSqlRelation("teacher","tID","tname"));
    model_cou->select();
    model_cou->setHeaderData(0, Qt::Horizontal, tr("课程号"));
    model_cou->setHeaderData(1, Qt::Horizontal, tr("课程名称"));
    model_cou->setHeaderData(2, Qt::Horizontal, tr("授课老师"));
    model_cou->setHeaderData(3, Qt::Horizontal, tr("上课学期"));
    table_cou->setModel(model_cou);
    table_cou->setItemDelegate(new QSqlRelationalDelegate(table_cou));
}

void AdminCouWidget::click_add()
{
    int rowNum = model_cou->rowCount(); //获得表的行数
    model_cou->insertRow(rowNum); //添加一行
}

void AdminCouWidget::click_cancel()
{
    model_cou->revertAll();
}

void AdminCouWidget::click_delete()
{
    int curRow = table_cou->currentIndex().row();//获取选中的行
    if(curRow<0)
    {
        return;
    }
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),
                         QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
       //如果不删除
    }
    else
    {
        model_cou->removeRow(curRow);
        //删除该行
        model_cou->submitAll(); //否则提交，在数据库中删除该行
    }
}
void AdminCouWidget::click_search()
{
    if(lineedit_cid->text().isEmpty())
    {
        model_cou->setTable("course");
        model_cou->select();
        model_cou->setHeaderData(0, Qt::Horizontal, tr("课程号"));
        model_cou->setHeaderData(1, Qt::Horizontal, tr("课程名称"));
        model_cou->setHeaderData(2, Qt::Horizontal, tr("授课老师"));
        model_cou->setHeaderData(3, Qt::Horizontal, tr("上课学期"));
    }
    else
    {
        QString indextid = lineedit_cid->text();
        model_cou->setFilter(QObject::tr("sID like '%%1%'").arg(indextid)); //根据tid进行筛选
        model_cou->select(); //显示结果
    }
}
void AdminCouWidget::click_submit()
{
    model_cou->database().transaction(); //开始事务操作
    if (model_cou->submitAll()) {
        model_cou->database().commit(); //提交
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("修改成功！"));
    }
    else
    {
        model_cou->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_cou->lastError().text()));
    }
}
void AdminCouWidget::change_combox()
{
    int indextime=combobox_currenttime->currentIndex()+1;
    QSqlQuery sql_query;
    QString updatesql="update nowtime set ntime=?";
    sql_query.prepare(updatesql);
    sql_query.bindValue(0,indextime);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError().text();
    }
    else
    {

    }
}
