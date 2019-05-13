#ifndef GALILEO_SHADER_H
#define GALILEO_SHADER_H

#include <iostream>
#include <vector>
#include <map>

#include "../../Common.h"
#include "../../Math/Matrix4f.h"

class Shader
{
public:

    virtual ~Shader();

    /**
     * Initialize shader program from given vertex and fragment shader code
     *
     * @param vertexShader vertex shader code
     * @param fragmentShader fragment shader code
     * @return true if shader initialized false otherwise
     */
    bool Initialize(const std::string& vertexShader, const std::string& fragmentShader);

    /**
     * Bind the shader for drawing
     */
    void Bind();

    /**
     * Unbind current shader
     */
    void Unbind();

    /**
     * Create uniform identified by name
     * this allow bouding value from code to shader
     * should be used when need to set value from code
     *
     * @param uniformName name of the uniform to be created
     * @return true if uniform has been created, false otherwise
     */
    bool CreateUniform(const std::string& uniformName);

    /**
     * Construct several uniforms
     *
     * @param uniformNames list of uniforms to create
     * @return true if all creation are successful, false otherwise
     */
    bool CreateUniforms(const std::vector<std::string>& uniformNames);

    /**
     * Set uniform matrix value
     *
     * @param uniform uniform name (must call create uniform before)
     * @param value matrix value
     */
    void SetUniform(const std::string& uniform, const Matrix4f& value);

    /**
     * Set uniform integer value
     */
    void SetUniform(const std::string& uniform, int value);

private:
    GLuint _programId;
    std::map<std::string, GLint> _uniforms;

    /**
     * Load given shader and return his id
     *
     * @param shader shader code to load
     * @param shaderType type of shader
     * @return shader code id or -1 if error
     */
    GLuint LoadShader(const std::string& shader, const GLenum& shaderType);
};


#endif //GALILEO_SHADER_H
