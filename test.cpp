#include "test.h"
#include <QDebug>
#include "Logger.h"
#include <sstream>
using namespace std;
extern Logger logger;
extern  stringstream logout;
Test::Test(QObject *parent) : QObject(parent)
{
  // Test::spdlog_init();
}
void Test::doWork(const QString &s)
{
    
  qDebug() <<   "doWork"; 
  logger.debug("doWork debug test.");
  logger.info("doWork info test.");
  logger.warn("doWork warn test.");

  emit sigResultReady(s);
}

void Test::onTest(const QString &s)
{
  qDebug() << s << s << s;
}


Q_INVOKABLE QString Test::button1Clicked()
{
  static int counter = 0;
   Test::doWork("test2");
   //emit sigResultReady("thread button1Clicked");
  return QString("button1 clicked %1 times").arg(++counter);
}

Q_INVOKABLE QString Test::button2Clicked()
{
  static int counter = 0;
  return QString("button2 clicked %1 times").arg(++counter);
}
