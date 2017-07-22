#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QRadioButton>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QFormLayout>
#include<QHBoxLayout>
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

signals:
    void display(int number,QString id);
public slots:
    //槽函数
    //登录按钮点击的槽函数
    void login_action();
    //退出按钮对应的槽函数
    void quit_action();

private:
    //私有控件
    QLabel *label_name;
    QLabel *label_passwd;
    QLineEdit *lineedit_name;
    QLineEdit *lineedit_passwd;
    QRadioButton *radio_manager;
    QRadioButton *radio_teacher;
    QRadioButton *radio_student;
    QPushButton *button_login;
    QPushButton *button_close;
    QFormLayout *formlayout_loginform;
    QHBoxLayout *hlayout_radio;
    //私有函数
    //初始化布局
    void init_layout();
    //初始化信号和槽函数
    void init_connect();
};

#endif // LOGINWIDGET_H
