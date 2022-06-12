
#include <Logger.h>

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
//#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

#include <vector>
#include <iostream>

void Logger::initLogger(std::string logPath, bool verbose, std::string logName)
{
    try
    {
        std::vector<spdlog::sink_ptr> sinks;

        if (verbose)
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::debug);
            console_sink->set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
            sinks.push_back(console_sink);
        }

        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(logPath + logName + "_log.txt", 2, 30);
        daily_sink->set_level(spdlog::level::info);
        //daily_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");
        daily_sink->set_pattern("[%H:%M:%S.%e] [%t] [%^%l%$] %v");
        sinks.push_back(daily_sink);

        // // rotating file sink for error and warn logs
        // auto console_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logPath + logName + "_error_log.txt", 1024 * 1024 * 5, 1, false);
        // console_sink->set_level(spdlog::level::warn);
        // sinks.push_back(console_sink);

        // // rotating file sink for all logs
        // sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logPath + logName + "_info_log.txt", 1024 * 1024 * 5, 1, false));

        // create synchronous  loggers
        auto readerLogger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
        readerLogger->set_level( spdlog::level::debug);
        readerLogger->flush_on(spdlog::level::warn);

        // globally register the loggers so they can be accessed using spdlog::get(logger_name)
        spdlog::register_logger(readerLogger);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Logger::debug(std::string log)
{
    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get("logger");
    logger->debug(log);
}

void Logger::info(std::string log)
{
    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get("logger");
    logger->info(log);
}

void Logger::warn(std::string log)
{
    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get("logger");
    logger->warn(log);
}

void Logger::error(std::string log)
{
    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get("logger");
    logger->error(log);
}
