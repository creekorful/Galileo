#ifndef GALILEO_OBJFILELOADER_H
#define GALILEO_OBJFILELOADER_H

#include <iostream>

#include "../Mesh.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector2.h"
#include "../../../IO/Files.h"
#include "../../../Util/Strings.h"

struct IndexGroup
{
    int positionIndex;
    int textureIndex;
    int normalIndex;
} typedef IndexGroup;

class ObjFileLoader
{
public:
    explicit ObjFileLoader(const std::string& filePath);

    Mesh* ReadMesh(Texture* pTexture);

private:
    Logger _logger;
    std::vector<std::string> _lines;

    static Mesh* BuildMesh(const std::vector<Vector3f>& vertices,
                   const std::vector<Vector2f>& uvs,
                   const std::vector<Vector3f>& normals,
                   const std::vector<std::vector<IndexGroup>>& faces, Texture *pTexture);
};


#endif //GALILEO_OBJFILELOADER_H
