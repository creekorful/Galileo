#ifndef GALILEO_STRINGS_H
#define GALILEO_STRINGS_H

#include <iostream>
#include <vector>

class Strings
{
public:
    static std::vector<std::string> Split(const std::string& string, char delimiter);
};


#endif //GALILEO_STRINGS_H
