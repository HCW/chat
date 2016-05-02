#include "infowidget.h"
#include <QDebug>
#include<QHeaderView>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include <QSqlError>
InfoWidget::InfoWidget(QString info_uno)
{
    m_info_uno=info_uno;//保存用户登录账号

    this->setWindowTitle("个人信息");
    this->setWindowIcon(QIcon(QPixmap("./info.png")));

    m_view=new QTableView;
    m_model=new QSqlTableModel;
    m_view->setModel(m_model);//设置model与view关联

    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置view手动提交数据

    m_model->setTable("UserTable");//设置要访问的数据库表
    m_model->setFilter("uno='"+m_info_uno+"'");
    //m_model->setFilter("uno='201324131218'");
    m_model->select();
   //设置表格显示的标题
    m_model->setHeaderData(0,Qt::Horizontal,"账号");
    m_model->setHeaderData(1,Qt::Horizontal,"用户名");
    m_model->setHeaderData(2,Qt::Horizontal,"性别");
    m_model->setHeaderData(3,Qt::Horizontal,"年龄");
    m_model->setHeaderData(4,Qt::Horizontal,"密码");

    QHBoxLayout*lay2=new QHBoxLayout;
    m_button_back=new QPushButton("返回主界面");
    m_button_update=new QPushButton("修改");
    lay2->addStretch(1);
    lay2->addWidget(m_button_back);
    lay2->addSpacing(20);
    lay2->addWidget(m_button_update);
    lay2->addStretch(1);

    QHBoxLayout*lay1=new QHBoxLayout;
    lay1->addWidget(m_view);

    QVBoxLayout*vlay=new QVBoxLayout(this);
    vlay->addLayout(lay1);
    vlay->addLayout(lay2);
    this->resize(550,100);
   /*-----------------上面是布局与初始化-------------------------*/
    connect(m_button_update,SIGNAL(clicked()),this,SLOT(slotupdatesummit()));

}
void InfoWidget::slotshow(QString str)
{
    this->m_info_uno=str;
    this->show();

}
void InfoWidget::slotupdatesummit()
{
    if(!m_model->submitAll())
    {
        qDebug()<<QSqlDatabase().lastError().text();
        m_model->database().rollback();//如果提交失败，则数据回滚，回复到原来的样子
    }
    else
    {
       m_model->database().commit();
    }
}
