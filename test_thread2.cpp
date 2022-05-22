#include "test_thread2.h"
#include <QDebug>

Test_Thread2::Test_Thread2(QObject *parent) : QObject(parent)
{
}

void Test_Thread2::doWork(const QString &s)
{
  qDebug() <<   "doWork"; 
  emit sigResultReady(s);
}

void Test_Thread2::onTest(const QString &s)
{
  qDebug() << s << s << s;
}

void Test_Thread2::on_pushButton_clicked()
{
  // Test_Thread* ts_th = new Test_Thread(this);
  // connect(ts_th, &Test_Thread::sigResultReady, this, &MainWindow::onTest);
  // connect(ts_th, &Test_Thread::finished, ts_th, &Test_Thread::deleteLater);
  //  ts_th->start();
}

void Test_Thread2::on_pushButton_2_clicked()
{
  // test_2->doWork("test2");
}

void Test_Thread2::on_pushButton_3_clicked()
{
  // test_concurent->show();
}

Q_INVOKABLE QString Test_Thread2::button1Clicked()
{
  static int counter = 0;
    Test_Thread2::doWork("test2");
  return QString("button1 clicked %1 times").arg(++counter);
}

Q_INVOKABLE QString Test_Thread2::button2Clicked()
{
  static int counter = 0;
  return QString("button2 clicked %1 times").arg(++counter);
}
