#include "main.h"
#include "test.h"
#include <sstream>

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#include <filesystem>
namespace fs = std::filesystem;
//using namespace std::filesystem;

using namespace std;
Logger logger;

stringstream logout;
extern int numcpp_test();
extern int fileTest();
extern int folder_exists();
// 字符串反转
QString stringInversion(QString str) {
  QString tmp;
  for (auto ch : str)
    tmp.prepend(ch);
  return tmp;
}
int folder_exists(const fs::path& p, fs::file_status s = fs::file_status{})
{
   // std::cout << p;
    if(fs::status_known(s) ? fs::exists(s) : fs::exists(p)){
//std::cout << " exists\n";
        return true;
    }
        
    else
    {
        //std::cout << " does not exist\n";
        return false;
    }
      
}

int fileTest()
{

fs::path folder_path2="/home/youngday/file-test2/";

if(!folder_exists(folder_path2)){
if (fs::create_directory(folder_path2))
{
	cout << "fs create dir succ: " << folder_path2 << endl;
}
else {
cout << "fs not created." << folder_path2 << endl;
}
}else {
cout << "fs has existed." << folder_path2 << endl;
};


    return true;
}
int main(int argc, char *argv[]) {

  // logout="sdfsdf";
  logger.initLogger("./log/", 1, "main");

  logger.debug("main debug test.");
  logger.info("main info test.");
  logger.warn("main warn test.");
  // spdlog_init();
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  QThread *my_thread = new QThread;
  Test *test_2 = new Test(); // should not (this) , QObject::moveToThread:
                             // Cannot move objects with a parent
  //  Test_Concurent* test_concurent = Q_NULLPTR;

  engine.addImportPath(TaoQuickImportPath);
  engine.rootContext()->setContextProperty("taoQuickImagePath",
                                           TaoQuickImagePath);
  engine.rootContext()->setContextProperty("buttonsClicked", test_2);

  test_2->moveToThread(my_thread);
  QObject::connect(test_2, &Test::sigResultReady, test_2, &Test::onTest);
  QObject::connect(my_thread, &QThread::finished, test_2, &Test::deleteLater);
  my_thread->start();
  // test_concurent = new Test_Concurent();
  // test_concurent->hide();

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
 // engine.load(url);

  QList<QString> strList;
  for (int i = 0; i < 20; i++)
    strList.append(QString::number(i + 1) + " ok");
  qDebug() << strList;

  QList<QString> strNew =
      QtConcurrent::blockingMapped(strList, stringInversion);
  qDebug() << strNew;

  // QSharedPointer<QMediaPlayer> player(new QMediaPlayer);
  // // https://www.luyinzhushou.com/text2voice/
  // player->setMedia(QUrl::fromLocalFile("test2.mp3")); // should local file
  // path
  // // player->setMedia(QUrl("qrc:/test1.mp3"));
  // player->setVolume(50); // 0~100音量范围,默认是100
  // player->play();

  numcpp_test();

fileTest();

  return app.exec();
}
