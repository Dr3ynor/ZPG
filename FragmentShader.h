#pragma once

#include "ShaderBase.h"

class FragmentShader : public ShaderBase
{
public:
    FragmentShader();
    ~FragmentShader() = default;

private:
    GLenum getShaderType() const override;
    GLenum shaderType = GL_FRAGMENT_SHADER;
};
