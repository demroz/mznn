#include "LogManager.hpp"

std::shared_ptr<spdlog::logger> LogManager::s_Logger;

void LogManager::init(const std::string& logFilePath) {
    try {
        std::vector<spdlog::sink_ptr> sinks;

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%T] [%^%l%$] %v");
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);
        file_sink->set_pattern("[%Y-%m-%d %T] [%l] %v");

        sinks.push_back(console_sink);
        sinks.push_back(file_sink);

        s_Logger = std::make_shared<spdlog::logger>("MultiSink", begin(sinks), end(sinks));
        spdlog::register_logger(s_Logger);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::info);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}

std::shared_ptr<spdlog::logger>& LogManager::getLogger() {
    return s_Logger;
}
