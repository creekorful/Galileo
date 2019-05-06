#include "Shader.h"

bool Shader::Initialize(const std::string& vertexShader, const std::string& fragmentShader)
{
    Logger logger = LoggerFactory::CreateLogger("Shader");

    GLuint vertexShaderId = LoadShader(vertexShader, GL_VERTEX_SHADER);
    if (vertexShaderId == -1)
    {
        logger.Error("Unable to load vertex shader");
        return false;
    }
    GLuint fragmentShaderId = LoadShader(fragmentShader, GL_FRAGMENT_SHADER);
    if (fragmentShaderId == -1)
    {
        logger.Error("Unable to load fragment shader");
        return false;
    }

    // Reached this point both shader has been compiled successfully
    _programId = glCreateProgram();
    if (_programId == 0)
    {
        logger.Error("Unable to create program");
        return false;
    }

    // Attach built shader to the program
    glAttachShader(_programId, vertexShaderId);
    glAttachShader(_programId, fragmentShaderId);

    // todo bind attrib location dynamically?

    glBindAttribLocation(_programId, 0, "in_Position");

    // finally link the program (build binary code)
    glLinkProgram(_programId);
    GLint isLinked;
    glGetProgramiv(_programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        logger.Error("Unable to link shader");
        return false;
    }

    // Not needed anymore, can be deleted
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return true;
}

GLuint Shader::LoadShader(const std::string& shader, const GLenum& shaderType)
{
    Logger logger = LoggerFactory::CreateLogger("Shader");

    GLuint shaderId = glCreateShader(shaderType);
    const char* c_str = shader.c_str();

    // Load shader source code
    glShaderSource(shaderId, 1, &c_str, nullptr);

    // Compile given shader
    glCompileShader(shaderId);

    // check compile status
    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        int maxLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
        char* log = new char[maxLength];
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, log);
        logger.Error(log);
        free(log);
        return -1;
    }

    return shaderId;
}

void Shader::Bind()
{
    assert(_programId != 0);
    glUseProgram(_programId);
}

void Shader::Unbind()
{
    assert(_programId != 0);
    glUseProgram(0);
}

Shader::~Shader()
{
    assert(_programId != 0);
    glDeleteProgram(_programId);
}

bool Shader::CreateUniform(const std::string& uniformName)
{
    GLint uniform = glGetUniformLocation(_programId, uniformName.c_str());

    if (uniform != -1)
    {
        // todo check not taken?
        _uniforms[uniformName] = uniform;
        return true;
    }

    return false;
}

void Shader::SetUniform(const std::string& uniform, const Matrix4f& value)
{
    glUniformMatrix4fv(_uniforms[uniform], 1, GL_FALSE, value.First());
}

void Shader::SetUniform(const std::string& uniform, int value)
{
    glUniform1i(_uniforms[uniform], value);
}
