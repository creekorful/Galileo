#include "Files.h"

std::string Files::Read(const std::string& path)
{
    std::ifstream file;
    file.open(path);

    std::stringstream outStream;
    outStream << file.rdbuf();
    return outStream.str();
}

std::vector<std::string> Files::ReadLines(const std::string& path)
{
    std::vector<std::string> lines;
    std::string currentLine;
    std::ifstream file;
    file.open(path);

    while (std::getline(file, currentLine))
    {
        lines.push_back(currentLine);
    }

    return lines;
}
