#ifndef GALILEO_MESHFACTORY_H
#define GALILEO_MESHFACTORY_H

#include "Mesh.h"
#include "../../Common.h"

class MeshFactory
{
public:
    static Mesh BuildPlaneMesh();

    static Mesh BuildCubeMesh(Texture* pTexture);
};


#endif //GALILEO_MESHFACTORY_H
