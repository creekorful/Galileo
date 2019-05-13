#include "MeshFactory.h"

MeshFactory::MeshFactory() : _logger(LoggerFactory::CreateLogger("MeshFactory"))
{
}

MeshFactory::~MeshFactory()
{
    for (auto& mesh : _meshs)
    {
        delete mesh.second;
    }
}

bool MeshFactory::LoadMesh(const std::string& file, const std::string& name, Texture* pTexture)
{
    _logger.Info("Loading mesh from: " + file + " with name: " + name);

    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    if (ext == ".obj")
    {
        ObjFileLoader loader(file);
        _meshs[name] = loader.ReadMesh(pTexture);
        return _meshs[name] != nullptr;
    }

    return false;
}

Mesh& MeshFactory::GetMesh(const std::string& name)
{
    return *_meshs[name];
}
