#include "adminstuwidget.h"
#include<QHeaderView>
#include<QMessageBox>
AdminStuWidget::AdminStuWidget(QWidget *parent) : QWidget(parent)
{
    init_layout();
    init_connect();
    init_data();
}
void AdminStuWidget::init_layout()
{
    label_sid=new QLabel("学号");
    label_sid->setParent(this);
    lineedit_sid=new QLineEdit(this);
    button_search=new QPushButton("搜索",this);
    button_submit=new QPushButton("提交修改",this);
    button_cancel=new QPushButton("撤销修改",this);
    button_add=new QPushButton("添加记录",this);
    button_delete=new QPushButton("删除记录",this);
    hlayout_search=new QHBoxLayout();
    hlayout_search->addWidget(label_sid);
    hlayout_search->addWidget(lineedit_sid);
    hlayout_search->addWidget(button_search);
    hlayout_search->addStretch();
    vlayout_left=new QVBoxLayout();
    vlayout_left->addLayout(hlayout_search);
    table_stu=new QTableView(this);
    vlayout_left->addWidget(table_stu);
    table_stu->setMinimumSize(450,300);
    table_stu->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_stu->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_stu->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    table_stu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //列宽度自适应
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

void AdminStuWidget::init_connect()
{
    connect(button_search,&QPushButton::clicked,this,&AdminStuWidget::click_search);
    connect(button_submit,&QPushButton::clicked,this,&AdminStuWidget::click_submit);
    connect(button_cancel,&QPushButton::clicked,this,&AdminStuWidget::click_cancel);
    connect(button_add,&QPushButton::clicked,this,&AdminStuWidget::click_add);
    connect(button_delete,&QPushButton::clicked,this,&AdminStuWidget::click_delete);
}

void AdminStuWidget::init_data()
{
    model_stu=new QSqlTableModel(this);
    model_stu->setTable("student");
    model_stu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_stu->select();
    model_stu->setHeaderData(0, Qt::Horizontal, tr("学号"));
    model_stu->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model_stu->setHeaderData(2, Qt::Horizontal, tr("密码"));
    model_stu->setHeaderData(3, Qt::Horizontal, tr("性别"));
    model_stu->setHeaderData(4, Qt::Horizontal, tr("生日"));
    model_stu->setHeaderData(5, Qt::Horizontal, tr("专业"));
    model_stu->setHeaderData(6, Qt::Horizontal, tr("年级"));
    table_stu->setModel(model_stu);
}

void AdminStuWidget::click_add()
{
    int rowNum = model_stu->rowCount(); //获得表的行数
    model_stu->insertRow(rowNum); //添加一行
}
void AdminStuWidget::click_cancel()
{
    model_stu->revertAll();
}
void AdminStuWidget::click_delete()
{
    int curRow = table_stu->currentIndex().row();//获取选中的行
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
        model_stu->removeRow(curRow);
        //删除该行
        model_stu->submitAll(); //否则提交，在数据库中删除该行
    }
}
void AdminStuWidget::click_search()
{
    if(lineedit_sid->text().isEmpty())
    {
        model_stu->setTable("student");
        model_stu->select();
        model_stu->setHeaderData(0, Qt::Horizontal, tr("学号"));
        model_stu->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model_stu->setHeaderData(2, Qt::Horizontal, tr("密码"));
        model_stu->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model_stu->setHeaderData(4, Qt::Horizontal, tr("生日"));
        model_stu->setHeaderData(5, Qt::Horizontal, tr("专业"));
        model_stu->setHeaderData(6, Qt::Horizontal, tr("年级"));
    }
    else
    {
        QString indextid = lineedit_sid->text();
        model_stu->setFilter(QObject::tr("sID like '%%1%'").arg(indextid)); //根据tid进行筛选
        model_stu->select(); //显示结果
        /*
        model_stu->setHeaderData(0, Qt::Horizontal, tr("教师号"));
        model_stu->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model_stu->setHeaderData(2, Qt::Horizontal, tr("密码"));
        */
    }
}
void AdminStuWidget::click_submit()
{
    model_stu->database().transaction(); //开始事务操作
    if (model_stu->submitAll()) {
        model_stu->database().commit(); //提交
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("修改成功！"));
    }
    else
    {
        model_stu->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_stu->lastError().text()));
    }
}
