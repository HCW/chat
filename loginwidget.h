#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
class LoginWidget : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWidget(QDialog *parent = 0);

private:
    QPushButton*m_button_login;
    QPushButton*m_button_quit;
    QLabel*m_label_user;
    QLabel*m_label_pwd;
    QLabel*m_label_zc;
    QLabel*m_label_fogetpwd;

    QLineEdit*m_lineedir_user;
    QLineEdit*m_lineedit_pwd;

signals:
    void signalloginsuccess(QString);
public slots:
    void slotloginbuttonclick();
};

#endif // LOGINWIDGET_H
