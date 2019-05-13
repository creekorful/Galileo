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

Mesh* MeshFactory::Load(const std::string& file, const std::string& name, Texture* pTexture)
{
    _logger.Info("Loading mesh from: " + file + " with name: " + name);

    // Compute extension
    std::string ext = file.substr(file.find_last_of('.'));

    Mesh* pMesh = nullptr;
    if (ext == ".obj")
    {
        ObjFileLoader loader(file);
        pMesh = loader.ReadMesh(pTexture);
    }

    if (pMesh != nullptr)
    {
        _logger.Info("Mesh loaded");
        _pMeshs[name] = pMesh;
    }

    return pMesh;
}

Mesh* MeshFactory::Get(const std::string& name)
{
    return _pMeshs[name];
}
