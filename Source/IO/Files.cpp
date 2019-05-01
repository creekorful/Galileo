#include "Files.h"

std::string Files::Read(const std::string& path)
{
    std::ifstream file;
    file.open(path);

    std::stringstream outStream;
    outStream << file.rdbuf();
    return outStream.str();
}
