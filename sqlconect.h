#ifndef SQLCONECT
#define SQLCONECT

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
void SqlDatabaseOpenInfo();


#endif // SQLCONECT
void SqlDatabaseOpenInfo()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("myapp.db");
    if(!db.open())
    {
       // QMessageBox::information(this,"提示","数据库打开失败！");
          qDebug()<<"Database open failed!";
        return;
    }
    qDebug()<<"Database open success!";
}
