#ifndef GALILEO_FILES_H
#define GALILEO_FILES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class Files
{
public:
    static std::string Read(const std::string& path);

    static std::vector<std::string> ReadLines(const std::string& path);
};


#endif //GALILEO_FILES_H
