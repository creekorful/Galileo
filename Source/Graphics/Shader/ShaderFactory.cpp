#include "ShaderFactory.h"

ShaderFactory::ShaderFactory(Logger logger) : _logger(std::move(logger))
{
}

bool ShaderFactory::Load(const std::string& name)
{
    _logger.Info("Loading shader: " + name);

    // Initialize shader
    std::string vertexShader = Files::Read("Shaders/" + name + "/vertex.vs");
    std::string fragmentShader = Files::Read("Shaders/" + name + "/fragment.fs");

    // Load shader
    if (!_shaders[name].Initialize(vertexShader, fragmentShader))
    {
        _logger.Error("Unable to initialize shader");
        _shaders.erase(name);
        return false;
    }

    _logger.Info("Shader loaded");

    return true;
}

Shader& ShaderFactory::Get(const std::string& name)
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
