#ifndef GALILEO_OBJFILELOADER_H
#define GALILEO_OBJFILELOADER_H

#include <iostream>

#include "../Mesh.h"
#include "../../../IO/Files.h"

class ObjFileLoader
{
public:
    explicit ObjFileLoader(const std::string& filePath);

    Mesh ReadMesh(Texture* pTexture);

private:
    Logger _logger;
    std::vector<std::string> _lines;
};


#endif //GALILEO_OBJFILELOADER_H
