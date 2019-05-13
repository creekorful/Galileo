#include "ShaderFactory.h"

ShaderFactory::ShaderFactory() : _logger(LoggerFactory::CreateLogger("ShaderFactory"))
{
}

ShaderFactory::~ShaderFactory()
{
    for (auto& shader : _shaders)
    {
        delete shader.second;
    }
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
    _shaders[name] = pShader;

    return pShader;
}

Shader* ShaderFactory::Get(const std::string& name)
{
    _logger.Debug("Get shader: " + name);
    return _shaders[name];
}

void ShaderFactory::Deinitialize(const std::string& name)
{
    _logger.Info("Deinitializing shader: " + name);
    if (_shaders.find(name) != _shaders.end())
    {
        _shaders.erase(name);
    }
}
