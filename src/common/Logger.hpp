#pragma once
#include <string>
#include <iostream>
#include <sstream>

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

class Logger
{
private:
    class LogImpl
    {
    public:
        LogImpl(Logger& log) : log_(log) {}
        ~LogImpl()
        {
            log_.print();
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

public:
    Logger(const std::string& str);
    ~Logger() = default;

    LogImpl operator<<(ELogSeverity severity)
    {
        stream_ << severityToString(severity) << prefix_ << " ";
        return LogImpl(*this);
    }

private:
    template <typename T>
    Logger& operator<<(const T& value)
    {
        stream_ << value;
        return *this;
    }

    void print() const;

    const std::string severityToString(ELogSeverity severity) const;

private:
    const std::string prefix_;
    std::ostringstream stream_;
};

} // namespace common
} // namespace casisco
