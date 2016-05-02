#include "loginwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlTableModel>
#include<QSqlRecord>
#include <QDebug>
#include "mainwindow.h"
#include <QProcess>
LoginWidget::LoginWidget(QDialog *parent) : QDialog(parent)
{

    this->resize(400,300);
    this->setWindowTitle("LoginInfo");
    this->setWindowIcon(QIcon(QPixmap("./login.png")));
    this->setBackgroundRole(QPalette::Background);
    m_button_login=new QPushButton("Login");
    m_button_quit=new QPushButton("Cancel");
    m_label_user=new QLabel("Username:");
    m_label_pwd=new QLabel("Password:");
    m_lineedir_user=new QLineEdit;
    m_lineedit_pwd=new QLineEdit;
    m_label_zc=new QLabel("Register?");
    m_label_fogetpwd=new QLabel("Foget Password?");

    //网格布局，挤到中间
    QGridLayout*lay=new QGridLayout(this);
    lay->setRowStretch(0,1);
    lay->setColumnStretch(0,1);
    lay->setRowStretch(5,1);
    lay->setColumnStretch(3,1);
    //占据了第1行和第1列、第2列
    lay->addWidget(m_label_user,1,1);
    lay->addWidget(m_lineedir_user,1,2);
    //占据了第2行和第1列、第2列，为了挤到中间，需要在第0行、第0列、第5行、第3列加弹簧，这样就挤到中间
    lay->addWidget(m_label_pwd,2,1);
    lay->addWidget(m_lineedit_pwd,2,2);

    //lay->addWidget(m_button_login,3,1);
    //lay->addWidget(m_button_quit,3,2);
    QHBoxLayout *hlay1=new QHBoxLayout;//在网络布局里面嵌套平行布局
    hlay1->addWidget(m_button_login);
    hlay1->addSpacing(10);
    hlay1->addWidget(m_button_quit);
    lay->addLayout(hlay1,3,2);

    QHBoxLayout*hlay2=new QHBoxLayout;
    hlay2->addWidget(m_label_zc);
    hlay2->setStretch(0,5);
    hlay2->addWidget(m_label_fogetpwd);

    lay->addLayout(hlay2,4,2);
    /*-/////////上面是布局和界面初始化，下面是槽函数连接-------------------------------*/
    //connect(this,SIGNAL(destroyed(QObject*)),this,SLOT(close()));
    connect(m_button_quit,SIGNAL(clicked()),this,SLOT(close()));
    connect(m_button_login,SIGNAL(clicked()),this,SLOT(slotloginbuttonclick()));
}
void LoginWidget::slotloginbuttonclick()
{
    if(m_lineedir_user->text().isEmpty()||m_lineedit_pwd->text().isEmpty())
    {
        QMessageBox::warning(this,"提示","信息不能为空！");
        return ;
    }
    QSqlTableModel*model=new QSqlTableModel;
    model->setTable("UserTable");

    //测试插入数据
    #if 0
       QSqlRecord rec=model->record();
       rec.setValue("uno","201324131216");
       rec.setValue("uname","到山顶");
       model->insertRecord(-1,rec);
       model->submitAll();
    #endif
   //查询条件；即相当于sql语句的select里的while
    model->setFilter("uno='"+m_lineedir_user->text().trimmed()+"'");
    model->select();//执行select

    if(model->rowCount())//判断上述查询结果是否为空，不为空说明记录存在
    {
        model->setFilter("pwd='"+m_lineedit_pwd->text().trimmed()+"'");
        model->select();
        if(model->rowCount())//判断上述查询结果是否为空，不为空说明记录存在
        {
            //QMessageBox::information(this,"提示","登录成功！");
            qDebug()<<m_lineedir_user->text().trimmed();
            emit signalloginsuccess(m_lineedir_user->text().trimmed()); //如果用户登录账号信息密码正确，向主窗口发射信号
            this->close();//登录成功该窗口关闭
        }
        else
        {
            QMessageBox::warning(this,"提示","密码错误，请重新输入！");
            return ;
        }
    }
    else
    {
        QMessageBox::warning(this,"提示","用户账号错误或不存在，请重新输入！");
        return ;
    }
}

