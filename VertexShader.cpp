#include "VertexShader.h"

VertexShader::VertexShader() : ShaderBase(), shaderType(GL_VERTEX_SHADER)
{
}

GLenum VertexShader::getShaderType() const
{
    return GL_VERTEX_SHADER;
}
