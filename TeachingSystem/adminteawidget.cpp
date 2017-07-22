#include "adminteawidget.h"
#include<QHeaderView>
#include<QMessageBox>
AdminTeaWidget::AdminTeaWidget(QWidget *parent) : QWidget(parent)
{
    //初始化布局
    init_layout();
    //初始化连接
    init_connect();
    //初始化数据库数据载入
    init_data();

}

void AdminTeaWidget::init_layout()
{
    label_tid=new QLabel("教师号");
    label_tid->setParent(this);
    lineedit_tid=new QLineEdit(this);
    button_search=new QPushButton("搜索",this);
    button_submit=new QPushButton("提交修改",this);
    button_cancel=new QPushButton("撤销修改",this);
    button_add=new QPushButton("添加记录",this);
    button_delete=new QPushButton("删除记录",this);
    hlayout_search=new QHBoxLayout();
    hlayout_search->addWidget(label_tid);
    hlayout_search->addWidget(lineedit_tid);
    hlayout_search->addWidget(button_search);
    hlayout_search->addStretch();
    vlayout_left=new QVBoxLayout();
    vlayout_left->addLayout(hlayout_search);
    table_tea=new QTableView(this);
    vlayout_left->addWidget(table_tea);
    table_tea->setMinimumSize(450,300);
    table_tea->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_tea->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_tea->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    table_tea->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //列宽度自适应
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

void AdminTeaWidget::init_connect()
{
    connect(button_search,&QPushButton::clicked,this,&AdminTeaWidget::click_search);
    connect(button_submit,&QPushButton::clicked,this,&AdminTeaWidget::click_submit);
    connect(button_cancel,&QPushButton::clicked,this,&AdminTeaWidget::click_cancel);
    connect(button_add,&QPushButton::clicked,this,&AdminTeaWidget::click_add);
    connect(button_delete,&QPushButton::clicked,this,&AdminTeaWidget::click_delete);
}

void AdminTeaWidget::init_data()
{
    model_tea=new QSqlTableModel(this);
    model_tea->setTable("teacher");
    model_tea->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_tea->select();
    model_tea->setHeaderData(0, Qt::Horizontal, tr("教师号"));
    model_tea->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model_tea->setHeaderData(2, Qt::Horizontal, tr("密码"));
    table_tea->setModel(model_tea);
}

void AdminTeaWidget::click_add()
{
    int rowNum = model_tea->rowCount(); //获得表的行数
    model_tea->insertRow(rowNum); //添加一行
    model_tea->setData(model_tea->index(rowNum,0),"index");
    model_tea->setData(model_tea->index(rowNum,1),"index");
    model_tea->setData(model_tea->index(rowNum,2),"index");
}

void AdminTeaWidget::click_cancel()
{
    model_tea->revertAll();
}

void AdminTeaWidget::click_delete()
{
    int curRow = table_tea->currentIndex().row();//获取选中的行
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
        model_tea->removeRow(curRow);
        //删除该行
        model_tea->submitAll(); //否则提交，在数据库中删除该行
    }
}

void AdminTeaWidget::click_search()
{
    if(lineedit_tid->text().isEmpty())
    {
        model_tea->setTable("teacher");
        model_tea->select();
        model_tea->setHeaderData(0, Qt::Horizontal, tr("教师号"));
        model_tea->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model_tea->setHeaderData(2, Qt::Horizontal, tr("密码"));
    }
    else
    {
        QString indextid = lineedit_tid->text();
        model_tea->setFilter(QObject::tr("tID like '%%1%'").arg(indextid)); //根据tid进行筛选
        model_tea->select(); //显示结果
        /*
        model_tea->setHeaderData(0, Qt::Horizontal, tr("教师号"));
        model_tea->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model_tea->setHeaderData(2, Qt::Horizontal, tr("密码"));
        */
    }

}

void AdminTeaWidget::click_submit()
{
    model_tea->database().transaction(); //开始事务操作
    if (model_tea->submitAll()) {
        model_tea->database().commit(); //提交
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("修改成功！"));
    }
    else
    {
        model_tea->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_tea->lastError().text()));
    }
}
