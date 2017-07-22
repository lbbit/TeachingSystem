#ifndef STUSCOREWIDGET_H
#define STUSCOREWIDGET_H

#include <QWidget>
#include"dbconnection.h"
#include<QTableWidget>
class StuScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StuScoreWidget(QString id,QWidget *parent = 0);

signals:

public slots:

private:
    QTableWidget *table_score;
    QString sid;
    void init_data();
};

#endif // STUSCOREWIDGET_H
