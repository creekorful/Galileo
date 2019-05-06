#ifndef GALILEO_LOGGER_H
#define GALILEO_LOGGER_H

#include <iostream>

class Logger
{
public:
    explicit Logger(const std::string& name);

    void Message(const std::string& level, const std::string& message);

    void Info(const std::string& message);

    void Debug(const std::string& message);

    void Error(const std::string& message);

private:
    std::string _name;
};


#endif //GALILEO_LOGGER_H
