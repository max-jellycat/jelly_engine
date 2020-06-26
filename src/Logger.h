#pragma once

class Logger {
public:
    enum Level {
        LevelError = 0,
        LevelWarn,
        LevelTrace
    };

private:
    Level m_logLevel;

public:
    Logger();

    void SetLevel(Level level);

    void Error(const char *message) const;

    void Warn(const char *message) const;

    void Trace(const char *message) const;
};