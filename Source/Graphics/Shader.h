#ifndef GALILEO_SHADER_H
#define GALILEO_SHADER_H

#include <iostream>
#include <map>

#include "../Common.h"
#include "../Math/Matrix4f.h"

class Shader
{
public:

    virtual ~Shader();

    bool Initialize(const std::string &vertexShader, const std::string &fragmentShader);

    void Bind();

    void Unbind();

    /**
     * Create uniform identified by name
     * this allow bouding value from code to shader
     * should be used when need to set value from code
     *
     * @param uniformName name of the uniform to be created
     * @return true if uniform has been created, false otherwise
     */
    bool CreateUniform(const std::string &uniformName);

    /**
     * Set uniform matrix value
     *
     * @param uniform uniform name (must call create uniform before)
     * @param value matrix value
     */
    void SetUniform(const std::string& uniform, const Matrix4f& value);

private:
    GLuint _programId;
    std::map<std::string, GLint> uniforms;

    GLuint LoadShader(const std::string &shader, const GLenum &shaderType);
};


#endif //GALILEO_SHADER_H
