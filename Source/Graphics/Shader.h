#ifndef GALILEO_SHADER_H
#define GALILEO_SHADER_H

#include <iostream>

#include "../Common.h"

class Shader
{
public:

    virtual ~Shader();

    bool Initialize(const std::string &vertexShader, const std::string &fragmentShader);

    void Bind();

    void Unbind();

private:
    GLuint _programId;

    GLuint LoadShader(const std::string &shader, const GLenum &shaderType);
};


#endif //GALILEO_SHADER_H
