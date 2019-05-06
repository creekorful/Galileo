#include "Logger.h"

Logger::Logger(const std::string& name)
{
    _name = name;
}

void Logger::Message(const std::string& level, const std::string& message)
{
    std::cout << "[" << level << "] " << _name << " - " << message << std::endl;
}

void Logger::Info(const std::string& message)
{
    Message("INFO", message);
}

void Logger::Debug(const std::string& message)
{
    Message("DEBUG", message);
}

void Logger::Error(const std::string& message)
{
    Message("ERROR", message);
}
