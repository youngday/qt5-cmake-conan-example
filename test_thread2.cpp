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


Q_INVOKABLE QString Test_Thread2::button1Clicked()
{
  static int counter = 0;
   Test_Thread2::doWork("test2");
   //emit sigResultReady("thread button1Clicked");
  return QString("button1 clicked %1 times").arg(++counter);
}

Q_INVOKABLE QString Test_Thread2::button2Clicked()
{
  static int counter = 0;
  return QString("button2 clicked %1 times").arg(++counter);
}
