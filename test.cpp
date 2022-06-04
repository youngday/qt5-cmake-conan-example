#include "test.h"
#include <QDebug>

Test::Test(QObject *parent) : QObject(parent)
{
   Test::spdlog_init();
}
int Test::spdlog_init()
{
  
    console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[test] [%^%l%$] %v");

    daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("./log/test.txt", 2, 30);
    daily_sink->set_level(spdlog::level::info);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");

    spdlog::logger logger("test", {console_sink, daily_sink});
    logger.set_level(spdlog::level::debug);
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
    logger.flush();

    return 0;
}



void Test::doWork(const QString &s)
{
  qDebug() <<   "doWork"; 
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
