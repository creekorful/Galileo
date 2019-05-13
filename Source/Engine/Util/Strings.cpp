#include "Strings.h"

std::vector<std::string> Strings::Split(const std::string& string, const char delimiter)
{
    std::vector<std::string> lines;

    std::string current;
    for (char i : string)
    {
        if (i == delimiter)
        {
            lines.push_back(current);
            current = "";
        }
        else
        {
            current += i;
        }
    }

    // if there is char left in current, append it (because the last part won't be added)
    if (!current.empty())
    {
        lines.push_back(current);
    }

    return lines;
}
