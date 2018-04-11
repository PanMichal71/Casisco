#pragma once
#include <string>
#include <iostream>

namespace casisco
{
enum ELogSeverity
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

namespace common
{

class Logger;
class LogImpl
{
public:
    LogImpl(Logger& log) : log_(log) {}
    ~LogImpl()
    {
        std::cout << std::endl;
    }

    template <typename T>
    LogImpl& operator<<(const T& value)
    {
        log_ << value;
        return *this;
    }

private:
    Logger& log_;
};

class Logger
{
public:
    friend class LogImpl;
    Logger(const std::string& str);
    ~Logger() = default;

    LogImpl operator<<(ELogSeverity severity)
    {
        std::cout << severityToString(severity) << prefix_ ;
        return LogImpl(*this);
    }

private:
    template <typename T>
    Logger& operator<<(const T& value)
    {
        std::cout << value;
        return *this;
    }

    const std::string severityToString(ELogSeverity severity) const;

private:
    const std::string prefix_;
};

} // namespace common
} // namespace casisco
