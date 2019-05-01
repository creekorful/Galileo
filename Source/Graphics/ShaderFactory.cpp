#include "ShaderFactory.h"

Shader* ShaderFactory::Load(const std::string& name)
{
    // Initialize shader
    std::string vertexShader = Files::Read("Shaders/" + name + "/vertex.vs");
    std::string fragmentShader = Files::Read("Shaders/" + name + "/fragment.fs");

    // Load shader
    auto pShader = new Shader();
    if (!pShader->Initialize(vertexShader, fragmentShader))
    {
        fprintf(stderr, "Unable to initialise shader");
        return nullptr;
    }

    _pShaders[name] = pShader;

    return pShader;
}

Shader* ShaderFactory::Get(const std::string& name)
{
    return _pShaders[name];
}

void ShaderFactory::Deinitialize(const std::string& name)
{
    Shader* ptr = _pShaders[name];
    if (ptr != nullptr)
    {
        _pShaders.erase(name);
        delete ptr;
    }
}

ShaderFactory::~ShaderFactory()
{
    for (const auto &[key, value]: _pShaders)
    {
        delete value;
    }
}