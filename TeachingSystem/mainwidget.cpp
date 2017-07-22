#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    stackw=new QStackedLayout();
    lw=new LoginWidget(this);
    stackw->addWidget(lw);
    this->setLayout(stackw);
    connect(lw,&LoginWidget::display,this,&MainWidget::login);
}
void MainWidget::login(int index, QString id)
{
    if(index==1)
    {
        aw=new AdminWidget(id,this);
        stackw->addWidget(aw);
        stackw->setCurrentIndex(1);
        connect(aw,&AdminWidget::destroyed,this,&MainWidget::close);
    }
    else if(index==2)
    {
        tw=new TeacherWidget(id,this);
        stackw->addWidget(tw);
        stackw->setCurrentIndex(1);
        connect(tw,&AdminWidget::destroyed,this,&MainWidget::close);
    }
    else
    {
        stuw=new StudentWidget(id,this);
        stackw->addWidget(stuw);
        stackw->setCurrentIndex(1);
        connect(stuw,&AdminWidget::destroyed,this,&MainWidget::close);
    }
}
MainWidget::~MainWidget()
{

}
