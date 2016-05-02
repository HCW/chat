#include "mainwindow.h"
#include <QMenu>
#include<QAction>
#include<QDebug>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include<QMessageBox>
#include<QSqlRecord>
#include <QSqlQueryModel>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->resize(500,300);

    this->setWindowIcon(QIcon(QPixmap("./main.png")));
    //在MainWindow上添加菜单，首先新建一个QMenuBar对象，然后往QMenuBar添加QMenu对象，
    //点击QMenu出现子菜单则需要添加QAction对象
    m_menuBar=new QMenuBar(this);
    QMenu*info=new QMenu("&个人信息");
    m_menuBar->addMenu(info);

    QMenu *fileTrans=new QMenu("&文件传输");
    m_menuBar->addMenu(fileTrans);

    QAction*pinfo=new QAction("&个人信息",info);
    info->addAction(pinfo);
    QAction*pQuit=new QAction("&退出",info);
    info->addAction(pQuit);

    QAction *pRecFile=new QAction("&收文件",fileTrans);
    fileTrans->addAction(pRecFile);
    QAction *pSendFile=new QAction("&发文件",fileTrans);
    fileTrans->addAction(pSendFile);

    m_button_send=new QPushButton("Send");
    m_lineedit_send=new QLineEdit;
    m_text_show=new QTextBrowser;

    m_label_ip=new QLabel("对方主机地址：");
    m_lineedit_hostip=new QLineEdit;
    m_label_port=new QLabel("对方端口：");
    m_lineedit_port=new QLineEdit;
    m_label_localport=new QLabel("本机端口：");
    m_lineedit_localport=new QLineEdit;

    QHBoxLayout*hlayip=new QHBoxLayout;
    hlayip->addWidget(m_label_ip);
    hlayip->addWidget(m_lineedit_hostip);

    QHBoxLayout*hlayport=new QHBoxLayout;
    hlayport->addStretch(1);
    hlayport->addWidget(m_label_port);
    hlayport->addWidget(m_lineedit_port);

    QHBoxLayout*hlaylocal=new QHBoxLayout;
    hlaylocal->addStretch(1);
    hlaylocal->addWidget(m_label_localport);
    hlaylocal->addWidget(m_lineedit_localport);

    QVBoxLayout *vlayipport=new QVBoxLayout;
    vlayipport->addLayout(hlayip);
    vlayipport->addLayout(hlayport);
    vlayipport->addLayout(hlaylocal);
    vlayipport->addStretch(1);

    QHBoxLayout*hlayiptext=new QHBoxLayout;
    hlayiptext->addWidget(m_text_show);
    hlayiptext->addLayout(vlayipport);

    QHBoxLayout *hlay=new QHBoxLayout;
    hlay->addWidget(m_lineedit_send);
    hlay->addWidget(m_button_send);

    QVBoxLayout *vlay=new QVBoxLayout(this);
    vlay->addWidget(m_menuBar);
    vlay->addLayout(hlayiptext);
    vlay->addLayout(hlay);
   // vlay->setGeometry(QRect(50,50,300,300));
/*---------------------上面是布局与变量初始化---------------------------------*/
    _udp=new QUdpSocket;//创建UDP套接字
   // _udp->bind(9988);//绑定端口

    connect(_udp,SIGNAL(readyRead()),this,SLOT(slotreceudp()));
    connect(m_button_send,SIGNAL(clicked()),this,SLOT(slotsendudp()));


    connect(pinfo,SIGNAL(triggered()),this,SLOT(slotinfoshow()));
    connect(pQuit,SIGNAL(triggered()),this,SLOT(close()));
    //InfoWidget lnfowidget;
    //connect(this,SIGNAL(siginfowidgetshow(QString)),&lnfowidget,SLOT(slotshow(QString)));
    m_time=new QTime;
    m_date=new QDate;

    connect(m_lineedit_send,SIGNAL(returnPressed()),this,SLOT(slotsendudp()));//lineedit接收键盘回车键发送消息

    //文件传输槽函数
//    connect(pRecFile,SIGNAL(triggered()),this,SLOT(slotReceFile()));
//    connect(pSendFile,SIGNAL(triggered()),this,SLOT(slotSendFile()));

}
void MainWindow::slotshow(QString uno)
{
    this->m_uno=uno;
    //数据库
    QSqlQueryModel querymodel;
    querymodel.setQuery("select uname from UserTable where uno="+m_uno);
    QString m_uname=querymodel.record(0).value("uname").toString();
    qDebug()<<m_uname;
    this->setWindowTitle(m_uname+"应用客户端");//设置窗口标题
    this->show();
}
void MainWindow::slotthisshow()
{
    m_lw->close();
    this->show();
}
void MainWindow::slotinfoshow()
{
  //  emit siginfowidgetshow(m_uno);
    m_lw=new InfoWidget(m_uno);
    connect(m_lw->m_button_back,SIGNAL(clicked()),this,SLOT(slotthisshow()));
    this->hide();
    m_lw->show();
}
void MainWindow::slotreceudp()
{
    while(_udp->hasPendingDatagrams())
    {
        quint32 datagramSize = _udp->pendingDatagramSize();
        QByteArray buf(datagramSize, 0);
        _udp->readDatagram(buf.data(), buf.size());


        QString struname="";
        QString strmesage="";
        QString Buf;
        Buf.prepend(buf);//将QByteArray转换为QString

        //处理接收到的数据
        for(int i=0;i<Buf.size();++i)
        {
            if(Buf[i] == '\n')
            {
              for(int j=i+1;j<Buf.size();++j)
                  strmesage +=Buf[j];
                break;
            }
            else
            {
                struname +=Buf[i];
            }
        }
        m_text_show->append(struname+" "+m_time->currentTime().toString()+m_date->currentDate().toString()+"：");
        m_text_show->append(strmesage);
        qDebug()<<"struname:"<<struname;
        qDebug() <<"strmesage:"<< strmesage;
    }
}
void MainWindow::slotsendudp()
{
    if(m_lineedit_hostip->text().isEmpty()||m_lineedit_port->text().isEmpty()||
            m_lineedit_localport->text().isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入对方主机IP和端口号！");
        return ;
    }
    //获取数据库里的用户信息
   #if 0
    m_model->setTable("UserTable");
    m_model->setFilter("uno='"+m_uno+"'");
    m_model->select();
    QSqlRecord record=m_model->record();
    qDebug()<<record.value(0);
   #endif

    QSqlQueryModel querymodel;
    querymodel.setQuery("select uname from UserTable where uno="+m_uno);
    QString m_uname=querymodel.record(0).value("uname").toString();
    qDebug()<<m_uname;
    //获取用户输入的主机地址和端口号
    QString hostip=m_lineedit_hostip->text().trimmed();
    QString strport=m_lineedit_port->text().trimmed();
    QString strlocalport=m_lineedit_localport->text().trimmed();

    quint16 localport=quint16(strlocalport.toUInt());//类型转换
    quint16 port=quint16(strport.toUInt());
    _udp->bind(localport);//指定本机绑定的端口号
   // qDebug()<<port;
    QString str=m_lineedit_send->text();//发送的内容
    m_text_show->append(m_uname+"  "+m_time->currentTime().toString()+m_date->currentDate().toString()+"：\n"+str);
     m_uname +="\n";
     m_uname +=str;
    _udp->writeDatagram(m_uname.toUtf8(), QHostAddress(hostip),port);//指定对方的主机地址和端口并发送姓名，以换行符结束
   // _udp->writeDatagram(str.toUtf8(), QHostAddress(hostip),port);//指定对方的主机地址和端口并发送数据

    qDebug()<<m_uname.toUtf8();
}
//void MainWindow::slotReceFile()
//{
//  //  QProcess receiveFile;
//    //receiveFile.start("F:\Qt5Pro\build-TcpReceiveFile-Desktop_Qt_5_5_1_MinGW_32bit-Debug\debug\TcpReceiveFile.exe");
//   // m_receiveWindow=new ReceiveWindow;

//    //m_receiveWindow->show();
//    //m_sendWindow=new SendWindow;
//    //m_receiveWindow.show();
//}
//void MainWindow::slotSendFile()
//{

//}
