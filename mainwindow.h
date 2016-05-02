#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QSqlTableModel>
#include <QTableView>
#include "Infowidget.h"
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <QUdpSocket>
#include <QLabel>
#include <QTime>
#include <QDate>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QMenuBar*m_menuBar;

    QString m_uno;//保存登录的用户账号
    //建立model-view
    QSqlTableModel*m_model;
    QTableView*m_view;

    InfoWidget* m_lw;//个人信息子窗口

    QPushButton*m_button_send;
    QLineEdit *m_lineedit_send;
    QTextBrowser *m_text_show;

    QUdpSocket *_udp;//Udp套接字

    QLabel *m_label_ip;
    QLineEdit*m_lineedit_hostip;
    QLabel*m_label_port;
    QLineEdit*m_lineedit_port;

    QLabel*m_label_localport;
    QLineEdit*m_lineedit_localport;

    //定义时间
    QTime *m_time;
    QDate *m_date;

    //传输文件窗口
   // ReceiveWindow *m_receiveWindow;
    //SendWindow    *m_sendWindow;
signals:
    void siginfowidgetshow(QString);
public slots:
    void slotshow(QString);
    void slotinfoshow();//显示用户信息槽函数
    void slotthisshow();

    void slotreceudp();//接收消息
    void slotsendudp();//发送消息

    //文件传输
//    void slotReceFile();
//    void slotSendFile();
};

#endif // MAINWINDOW_H
