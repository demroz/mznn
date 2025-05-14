#ifndef __LOGMANAGER_HPP__
#define __LOGMANAGER_HPP__

#include <memory>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

class LogManager {
    public:
        static void init(const std::string& logFilePath = "/tmp/log.txt");
        static std::shared_ptr<spdlog::logger>& getLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
};

#ifndef NDEBUG
#define LOG_TRACE(...)       LogManager::getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)       LogManager::getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)        LogManager::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)        LogManager::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)       LogManager::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)    LogManager::getLogger()->critical(__VA_ARGS__)
#else
#define LOG_TRACE(...)       (void)0
#define LOG_INFO(...)       (void)0
#define LOG_DEBUG(...)        (void)0
#define LOG_WARN(...)        (void)0
#define LOG_CRITICAL(...)    LogManager::getLogger()->critical(__VA_ARGS__)
#endif

#endif // LOGMANAGER_H_
