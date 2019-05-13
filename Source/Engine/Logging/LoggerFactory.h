#ifndef GALILEO_LOGGERFACTORY_H
#define GALILEO_LOGGERFACTORY_H

#include <iostream>

#include "Logger.h"

class LoggerFactory
{
public:
    static LoggerFactory p()
    {
        static LoggerFactory instance;
        return instance;
    }

    static Logger CreateLogger(const std::string& name);
};


#endif //GALILEO_LOGGERFACTORY_H
