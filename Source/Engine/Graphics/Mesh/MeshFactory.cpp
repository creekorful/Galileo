#include "MeshFactory.h"

MeshFactory::MeshFactory() : _logger(LoggerFactory::CreateLogger("MeshFactory"))
{
}

MeshFactory::~MeshFactory()
{
    _logger.Debug("Cleaning up " + std::to_string(_pMeshs.size()) + " meshs");
    for (auto& mesh : _pMeshs)
    {
        delete mesh.second;
    }
    _logger.Debug("Cleanup done");
}

bool MeshFactory::LoadMesh(const std::string& file, const std::string& name, Texture* pTexture)
{
    _logger.Info("Loading mesh from: " + file + " with name: " + name);

    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    if (ext == ".obj")
    {
        ObjFileLoader loader(file);
        _pMeshs[name] = loader.ReadMesh(pTexture);
        return _pMeshs[name] != nullptr;
    }

    return false;
}

Mesh& MeshFactory::GetMesh(const std::string& name)
{
    return *_pMeshs[name];
}
