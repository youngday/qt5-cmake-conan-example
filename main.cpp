#include "main.h"
#include "test.h"
//#include "test_concurent.h"
namespace spd = spdlog;
/*****************************************
 * QtConcurrent blockingMapped 并发处理QList或者QMap
 ****************************************/

extern int numcpp_test();


// 字符串反转
QString stringInversion(QString str)
{
    QString tmp;
    for (auto ch : str)
        tmp.prepend(ch);
    return tmp;
}

int spdlog_init()
{
  
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[main] [%^%l%$] %v");

    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("./log/main.txt", 2, 30);
    daily_sink->set_level(spdlog::level::info);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");

    spdlog::logger logger("main", {console_sink, daily_sink});
    logger.set_level(spdlog::level::debug);
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
    logger.flush();

    return 0;
}


int main(int argc, char *argv[])
{
    spdlog_init();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QThread *my_thread = new QThread;
    Test *test_2 = new Test(); // should not (this) , QObject::moveToThread: Cannot move objects with a parent
    //  Test_Concurent* test_concurent = Q_NULLPTR;
    
    engine.addImportPath(TaoQuickImportPath);
    engine.rootContext()->setContextProperty("taoQuickImagePath", TaoQuickImagePath);
    engine.rootContext()->setContextProperty("buttonsClicked", test_2);

    test_2->moveToThread(my_thread);
    QObject::connect(test_2, &Test::sigResultReady, test_2, &Test::onTest);//youngday:TODO:
    QObject::connect(my_thread, &QThread::finished, test_2, &Test::deleteLater);
    my_thread->start();
    // test_concurent = new Test_Concurent();
    // test_concurent->hide();



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QList<QString> strList;
    for (int i = 0; i < 20; i++)
        strList.append(QString::number(i + 1) + " ok");
    qDebug() << strList;

    QList<QString> strNew = QtConcurrent::blockingMapped(strList, stringInversion);
    qDebug() << strNew;

    QSharedPointer<QMediaPlayer> player(new QMediaPlayer);
    // https://www.luyinzhushou.com/text2voice/
    player->setMedia(QUrl::fromLocalFile("/home/youngday/prjqt/mp3/test2.mp3")); // should local file path
    // player->setMedia(QUrl("qrc:/test1.mp3"));
    player->setVolume(50); // 0~100音量范围,默认是100
    player->play();

   
 numcpp_test();









    return app.exec();
}
