#ifndef TEST_CONCURENT_H
#define TEST_CONCURENT_H

//#include <QWidget>
#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace Ui {
class Test_Concurent;
}

class Test_Concurent 
{
   

public:
    explicit Test_Concurent();

    void star();
    void xunhuan();

    ~Test_Concurent();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::Test_Concurent *ui;
    int myEnable = 0;//标志位
    QList<int> numList;
};

#endif // TEST_CONCURENT_H
