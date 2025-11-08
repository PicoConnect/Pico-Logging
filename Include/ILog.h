#ifndef PICOLOGGING_ILOG_H
#define PICOLOGGING_ILOG_H

#include <string>

enum LogLevel
{
    LogTrace = 0,
    LogDebug = 1,
    LogInfo = 2,
    LogWarn = 3,
    LogError = 4,
    LogFatal = 5,
};

class ILog
{
public:
    virtual void Trace(const std::string& statement) const = 0;
    virtual void Debug(const std::string& statement) const = 0;
    virtual void Info(const std::string& statement) const = 0;
    virtual void Warn(const std::string& statement) const = 0;
    virtual void Error(const std::string& statement) const = 0;
    virtual void Fatal(const std::string& statement) const = 0;
    virtual LogLevel GetMinimumLogLevel() const = 0;
    virtual void SetMinimumLogLevel(LogLevel minimumLevel) = 0;
};



#endif //PICOLOGGING_ILOG_H
