#include "dbconnection.h"

DBConnection::DBConnection()
{

}
QSqlDatabase DBConnection::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("lbbteachingsystem");
    db.setPort(3306);
    //根据数据库进行配置
//    db.setUserName("lbb");
//    db.setPassword("zhang120");
    return db;
}
