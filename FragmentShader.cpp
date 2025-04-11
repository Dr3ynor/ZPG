#include "FragmentShader.h"

FragmentShader::FragmentShader() : ShaderBase(), shaderType(GL_FRAGMENT_SHADER)
{
}

GLenum FragmentShader::getShaderType() const
{
    return GL_FRAGMENT_SHADER;
}
