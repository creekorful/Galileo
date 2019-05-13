#include "LoggerFactory.h"

Logger LoggerFactory::CreateLogger(const std::string& name)
{
    //todo copy handlers etc
    return Logger(name);
}
