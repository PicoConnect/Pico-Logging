#ifndef PICOLOGGING_LOG_H
#define PICOLOGGING_LOG_H

#include <ILog.h>
#include <string>

class Log : public ILog
{
private:
    LogLevel m_minimumLogLevel;

    void DoLog(LogLevel level, std::string logStatement) const;
    std::string LogLevelToString(LogLevel level) const;

public:
    Log(LogLevel minimumLogLevel);

    // ILog
    void Trace(const std::string& statement) const override;
    void Debug(const std::string& statement) const override;
    void Info(const std::string& statement) const override;
    void Warn(const std::string& statement) const override;
    void Error(const std::string& statement) const override;
    void Fatal(const std::string& statement) const override;
    LogLevel GetMinimumLogLevel() const override;
    void SetMinimumLogLevel(LogLevel minimumLevel) override;
};

#endif //PICOLOGGING_LOG_H
