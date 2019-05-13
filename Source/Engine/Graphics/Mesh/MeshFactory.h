#ifndef GALILEO_MESHFACTORY_H
#define GALILEO_MESHFACTORY_H

#include <map>

#include "Mesh.h"
#include "../../Common.h"

#include "Loader/ObjFileLoader.h"

class MeshFactory
{
public:

    MeshFactory();

    ~MeshFactory();

    Mesh& GetMesh(const std::string& name);

    // TODO: uncouple texture from mesh
    bool LoadMesh(const std::string& file, const std::string& name, Texture* pTexture);

    static MeshFactory& p()
    {
        static MeshFactory instance;
        return instance;
    }

private:
    std::map<std::string, Mesh*> _pMeshs;
    Logger _logger;
};


#endif //GALILEO_MESHFACTORY_H
