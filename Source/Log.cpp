#include <Log.h>
#include <sstream>

extern "C"
{
    void sleep_ms(int ms);
}

Log::Log(LogLevel minimumLogLevel) : m_minimumLogLevel(minimumLogLevel)
{
    //setvbuf(stdout, NULL, _IONBF, 0);  // Disable buffering
}

void Log::DoLog(LogLevel level, std::string logStatement) const
{
    if (level < GetMinimumLogLevel())
    {
        return;
    }


    std::stringstream logBuf;
    auto levelStr = LogLevelToString(level);
    logBuf << "[";
    logBuf << levelStr;
    logBuf << "] ";

    for (char c : logStatement) // Filter unreadable characters
    {
        if (c >= 32 && c <= 126) // printable ASCII range
        {
            logBuf << c;
        }
        else if (c == '\n' || c == '\r' || c == '\t') // optional: allow newline, etc.
        {
            logBuf << c;
        }
        else
        {
            logBuf << "\\x" << std::hex << std::uppercase << static_cast<int>(c);
        }
    }

    // Prints max 256 characters and appends '\n' at the end.
    printf("%.256s\n", logBuf.str().c_str());
    fflush(stdout);
    //sleep_ms(10);
}

void Log::Trace(const std::string& statement) const
{
    DoLog(LogLevel::LogTrace, statement);
}

void Log::Debug(const std::string& statement) const
{
    DoLog(LogLevel::LogDebug, statement);
}

void Log::Info(const std::string& statement) const
{
    DoLog(LogLevel::LogInfo, statement);
}

void Log::Warn(const std::string& statement) const
{
    DoLog(LogLevel::LogWarn, statement);
}

void Log::Error(const std::string& statement) const
{
    DoLog(LogLevel::LogError, statement);
}

void Log::Fatal(const std::string& statement) const
{
    DoLog(LogLevel::LogFatal, statement);
}

LogLevel Log::GetMinimumLogLevel() const
{
    return m_minimumLogLevel;
}

void Log::SetMinimumLogLevel(LogLevel minimumLevel)
{
    m_minimumLogLevel = minimumLevel;
}

std::string Log::LogLevelToString(LogLevel level) const
{
    switch (level)
    {
        case LogTrace:
            return "TRACE";

        case LogDebug:
            return "DEBUG";

        case LogInfo:
            return "INFO";

        case LogWarn:
            return "WARN";

        case LogError:
            return "ERROR";

        case LogFatal:
            return "FATAL";

        default:
            return "UNKNOWN LOG LEVEL";
    }
}