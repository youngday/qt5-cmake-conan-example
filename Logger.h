#pragma once

#include <string>
/**
 * Simple wrapper around spdlog library
 */
class Logger {
public:
    /**
     * Initializes spdlog logger
     * @param logPath where log files will be saved
     * @param verbose if true logs will be printed to console
     * @param logName name of log file
     */
    static void initLogger(std::string logPath, bool verbose, std::string logName);

    static void debug(std::string log);
    static void info(std::string log);
    static void warn(std::string log);
    static void error(std::string log);
};
