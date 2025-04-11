#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // original #include <glm/ext/matrix_transform.hpp>

#include "ShaderBase.h"

class VertexShader : public ShaderBase
{
public:
    VertexShader();

    ~VertexShader() = default;

private:
    GLenum getShaderType() const override;
    GLenum shaderType = GL_VERTEX_SHADER;
};
