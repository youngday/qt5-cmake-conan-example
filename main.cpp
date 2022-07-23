#include "main.h"
#include "Logger.h"
#include "test.h"
#include <iostream>
#include <sstream>

#include <filesystem>
namespace fs = std::filesystem;
// using namespace std::filesystem;

using namespace std;
Logger logger;

stringstream logout;
extern int numcpp_test();
extern int folderTest();
extern int tcp_client();
extern int tcp_client_coro();
// 字符串反转
QString stringInversion(QString str)
{
  QString tmp;
  for (auto ch : str)
    tmp.prepend(ch);
  return tmp;
}

int folderTest()
{

  fs::path folder_path2 = "/home/youngday/file-test2/";
  int ret = false;
  logout.str("");
  if (!fs::exists(folder_path2))
  {
    if (fs::create_directory(folder_path2))
    {
      logout << "mkdir successed: " << folder_path2 << endl;
      ret = true;
    }
    else
    {
      logout << "mkdir failed." << folder_path2 << endl;
      ret = false;
    } // directory
  }
  else
  {
    logout << "fs has existed." << folder_path2 << endl;
    ret = true;
  }; // exist
  logger.debug(logout.str());
  return ret;
}
int main(int argc, char *argv[])
{

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
      [url](QObject *obj, const QUrl &objUrl)
      {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  // engine.load(url);

  QList<QString> strList;
  for (int i = 0; i < 20; i++)
    strList.append(QString::number(i + 1) + " ok");
  string text;
  for (int i = 0; i < strList.size(); ++i)
    text += strList.at(i).toStdString() + "  ";
  logger.debug(text);

  QList<QString> strNew =
      QtConcurrent::blockingMapped(strList, stringInversion);
  text.clear();
  for (int i = 0; i < strNew.size(); ++i)
    text += strNew.at(i).toStdString() + "  ";
  logger.debug(text);

  // QSharedPointer<QMediaPlayer> player(new QMediaPlayer);
  // // https://www.luyinzhushou.com/text2voice/
  // player->setMedia(QUrl::fromLocalFile("test2.mp3")); // should local file
  // path
  // // player->setMedia(QUrl("qrc:/test1.mp3"));
  // player->setVolume(50); // 0~100音量范围,默认是100
  // player->play();

 // numcpp_test();

 // folderTest();
// tcp_client();
 tcp_client_coro();

 Qt3DExtras::Quick::Qt3DQuickWindow view;
    view.setSource(QUrl("qrc:/qt3d.qml"));
    view.show();

  return app.exec();
}
