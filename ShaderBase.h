#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

class ShaderBase
{
public:
    bool readShader(const char *path);
    void attach(GLuint programID);

protected:
    void compile();
    virtual GLenum getShaderType() const = 0;

    std::string shaderSource;
    GLint shaderID;
};