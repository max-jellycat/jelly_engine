#include <iostream>
#include "Logger.h"

Logger::Logger()
    : m_logLevel(LevelTrace) {}

void Logger::SetLevel(Level level)
{
    m_logLevel = level;
}

void Logger::Error(const char *message) const
{
    if (m_logLevel == LevelError)
        std::cerr << "[ERROR]: " << message << std::endl;
}

void Logger::Warn(const char *message) const
{
    if (m_logLevel == LevelWarn)
        std::cout << "[WARNING]: " << message << std::endl;
}

void Logger::Trace(const char *message) const
{
    if (m_logLevel == LevelTrace)
        std::cout << "[TRACE]: " << message << std::endl;
}