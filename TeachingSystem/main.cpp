#include "mainwidget.h"
#include"adminwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QSqlDatabase db = DBConnection::initDB();
    if(!db.open())
    {
        qDebug()<<db.lastError().text();
        return 1;
    }
    /*
    MainWidget w;
    w.show();
    */

    /*
    LoginWidget lw;
    lw.show();
    */
    //AdminWidget aw;
    //aw.show();
    //TeaScoreWidget taw("t03");
    //taw.show();
    //TeacherWidget tw("t02");
    //tw.show();
    //StudentWidget scw("B14040905");
    //scw.show();
    MainWidget mw;
    mw.show();
    return a.exec();
}
