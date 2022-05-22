#ifndef TEST_THREAD2_H
#define TEST_THREAD2_H

#include <QObject>
#include <QDebug>

class Test_Thread2 : public QObject
{
    Q_OBJECT
public:
    explicit Test_Thread2(QObject *parent = 0);


    Q_INVOKABLE QString button1Clicked();
    Q_INVOKABLE QString button2Clicked();

signals:
    void sigResultReady(const QString &s);
public slots:
    void doWork(const QString &s);
    void onTest(const QString &s);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // TEST_THREAD2_H
