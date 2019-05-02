#include "ShaderFactory.h"

bool ShaderFactory::Load(const std::string& name)
{
    // Initialize shader
    std::string vertexShader = Files::Read("Shaders/" + name + "/vertex.vs");
    std::string fragmentShader = Files::Read("Shaders/" + name + "/fragment.fs");

    // Load shader
    if (!_shaders[name].Initialize(vertexShader, fragmentShader))
    {
        fprintf(stderr, "Unable to initialise shader");
        _shaders.erase(name);
        return false;
    }

    return true;
}

Shader& ShaderFactory::Get(const std::string& name)
{
    return _shaders[name];
}

void ShaderFactory::Deinitialize(const std::string& name)
{
    if (_shaders.find(name) != _shaders.end())
    {
        _shaders.erase(name);
    }
}