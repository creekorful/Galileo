#include "ShaderFactory.h"

ShaderFactory::ShaderFactory() : _logger(LoggerFactory::CreateLogger("ShaderFactory"))
{
}

ShaderFactory::~ShaderFactory()
{
    _logger.Debug("Cleaning up " + std::to_string(_pShaders.size()) + " shaders");
    for (auto& shader : _pShaders)
    {
        delete shader.second;
    }
    _logger.Debug("Cleanup done");
}

Shader* ShaderFactory::Load(const std::string& name)
{
    _logger.Info("Loading shader: " + name);

    // Initialize shader
    std::string vertexShader = Files::Read("Resources/Shaders/" + name + "/vertex.vs");
    std::string fragmentShader = Files::Read("Resources/Shaders/" + name + "/fragment.fs");

    // Load shader
    auto pShader = new Shader();
    if (!pShader->Initialize(vertexShader, fragmentShader))
    {
        _logger.Error("Unable to initialize shader");
        delete pShader;
        return nullptr;
    }

    _logger.Info("Shader loaded");
    _pShaders[name] = pShader;

    return pShader;
}

Shader* ShaderFactory::Get(const std::string& name)
{
    _logger.Debug("Get shader: " + name);
    return _pShaders[name];
}

void ShaderFactory::Deinitialize(const std::string& name)
{
    _logger.Info("Deinitializing shader: " + name);
    if (_pShaders.find(name) != _pShaders.end())
    {
        _pShaders.erase(name);
    }
}
