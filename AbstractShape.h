#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"

class AbstractShape
{
public:
    virtual void draw() = 0;

protected:
    VAO *vao;
    VBO *vbo;
};