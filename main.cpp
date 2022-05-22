#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMediaPlayer>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <memory>
#include "test_thread2.h"
//#include "test_concurent.h"
namespace spd = spdlog;
/*****************************************
 * QtConcurrent blockingMapped 并发处理QList或者QMap
 ****************************************/
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
    //创建文件名类似于： daily_log_2018-01-17_10-27.txt，如果程序不退出的话，就是每天2:30 am创建新的文件
    auto console = spd::daily_logger_mt("maitianPT", "./daily_log.txt", 2, 30);
    //写入文档
    console->info("test daily info 提示信息");
    console->warn("test daily warn 警告");
    console->error("test daily error 错误");
    console->critical("test daily critical 致命");
    return 0;
}

int main(int argc, char *argv[])
{
    spdlog_init();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

         // Test_Thread2 buttonsClicked;
       QThread *my_thread = Q_NULLPTR;
    Test_Thread2 *test_2 = Q_NULLPTR;
    //  Test_Concurent* test_concurent = Q_NULLPTR;

    test_2 = new Test_Thread2(); // should not (this) , QObject::moveToThread: Cannot move objects with a parent
    my_thread = new QThread;
    
    engine.addImportPath(TaoQuickImportPath);
    engine.rootContext()->setContextProperty("taoQuickImagePath", TaoQuickImagePath);
  engine.rootContext()->setContextProperty("buttonsClicked", test_2);

    test_2->moveToThread(my_thread);
        QObject::connect(test_2, &Test_Thread2::sigResultReady, test_2, &Test_Thread2::onTest);//youngday:TODO:
    QObject::connect(my_thread, &QThread::finished, test_2, &Test_Thread2::deleteLater);

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

   

    return app.exec();
}
