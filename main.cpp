#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <memory>
namespace spd = spdlog;
int spdlog_init()
{
	//创建文件名类似于： daily_log_2018-01-17_10-27.txt，如果程序不退出的话，就是每天2:30 am创建新的文件
	auto console= spd::daily_logger_mt("maitianPT", "./daily_log.txt", 2, 30);
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
    engine.addImportPath(TaoQuickImportPath);
    engine.rootContext()->setContextProperty("taoQuickImagePath", TaoQuickImagePath);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
