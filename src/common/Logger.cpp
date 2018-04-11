#include "Logger.hpp"

namespace casisco
{
namespace common
{

Logger::Logger(const std::string &str)
    :prefix_(str)
{

}

void Logger::print() const
{
    std::cout << stream_.str() << std::endl;
}

const std::string Logger::severityToString(ELogSeverity severity) const
{
    switch(severity)
    {
    case ELogSeverity::DEBUG:
        return "[DEBUG] ";
    case ELogSeverity::INFO:
        return "[INFO] ";
    case ELogSeverity::WARNING:
        return "[WARNING] ";
    case ELogSeverity::ERROR:
        return "[ERROR] ";
    default:
        return "[UNSUPPORTED SEVERITY TYPE!!!!!]";
    }
}

}
}
