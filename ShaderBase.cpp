#include "ShaderBase.h"

bool ShaderBase::readShader(const char *path)
{
    bool check = true;
    std::ifstream input;
    input.open(path);
    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            shaderSource += line + " \n ";
        }
        input.close();
    }
    else
    {
        std::cerr << "ShaderBase: Unable to open file " << path << std::endl;
        check = false;
    }
    if (!check)
        return false;
    this->compile();
    return true;
}

void ShaderBase::compile()
{
    shaderID = glCreateShader(this->getShaderType());
    const GLchar *v_shader = this->shaderSource.c_str();
    glShaderSource(shaderID, 1, &v_shader, NULL);
    glCompileShader(shaderID);
}

void ShaderBase::attach(GLuint programID)
{
    glAttachShader(programID, shaderID);
}
