#ifndef Test_H
#define Test_H

#include <QObject>
#include <QDebug>
#include "main.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);


    Q_INVOKABLE QString button1Clicked();
    Q_INVOKABLE QString button2Clicked();

signals:
    void sigResultReady(const QString &s);
public slots:
    void doWork(const QString &s);
    void onTest(const QString &s);
private:
    std::shared_ptr <spdlog::sinks::stdout_color_sink_mt > console_sink  ;
    std::shared_ptr <spdlog::sinks::daily_file_sink_mt > daily_sink ;
    int spdlog_init();
};

#endif // Test_H
