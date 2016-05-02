#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include<QTableView>
#include <QPushButton>
class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QString info_uno);

    //建立model-view
    QSqlTableModel*m_model;
    QTableView*m_view;

     QString m_info_uno;

    QPushButton*m_button_back;
    QPushButton*m_button_update;
signals:

public slots:
    void slotshow(QString);
    void slotupdatesummit();
};

#endif // INFOWIDGET_H
