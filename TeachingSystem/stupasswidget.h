#ifndef STUPASSWIDGET_H
#define STUPASSWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QFormLayout>
class StuPassWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StuPassWidget(QString sid,QWidget *parent = 0);

signals:

public slots:
    void click_confirm();
    void click_reset();
private:
    QLabel *label_oldpass;
    QLabel *label_newpass;
    QLabel *label_repass;
    QLineEdit *lineedit_oldpass;
    QLineEdit *lineedit_newpass;
    QLineEdit *lineedit_repass;
    QPushButton *button_confirm;
    QPushButton *button_reset;
    QFormLayout *formlayout_all;
    QString stuID;
    void init_layout();
    void init_connect();
};

#endif // STUPASSWIDGET_H
