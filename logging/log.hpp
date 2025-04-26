#ifndef __LOG_INITIALIZER_HPP__
#define __LOG_INITIALIZER_HPP__

#include "LogManager.hpp"

class LogInitializer {
public:
    LogInitializer() {
        LogManager::init(); // You can pass a file path here if needed
    }
};

// Define a global instance
static LogInitializer globalLoggerInitializer;

#endif // LOGGER_INITIALIZER_H
