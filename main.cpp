#include <QApplication>
#include "loginwidget.h"
#include "sqlconect.h"
#include "mainwindow.h"
#include "infowidget.h"
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);
    SqlDatabaseOpenInfo();//打开数据库
    LoginWidget l;
    l.show();
    MainWindow w;
   // w.show();
    //InfoWidget lw;
   // lw.show();
    QObject::connect(&l,SIGNAL(signalloginsuccess(QString)),&w,SLOT(slotshow(QString)));
    return app.exec();
}
