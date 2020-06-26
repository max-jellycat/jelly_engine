#include <iostream>
#include "Logger.h"

Logger::Logger()
        : logLevel(LevelTrace) {}

void Logger::SetLevel(Level level) {
    this->logLevel = level;
}

void Logger::Error(const char *message) const {
    if (this->logLevel == LevelError)
        std::cerr << "[ERROR]: " << message << std::endl;
}

void Logger::Warn(const char *message) const {
    if (this->logLevel == LevelWarn)
        std::cout << "[WARNING]: " << message << std::endl;
}

void Logger::Trace(const char *message) const {
    if (this->logLevel == LevelTrace)
        std::cout << "[TRACE]: " << message << std::endl;
}