#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Window.h"
#include <glm/glm.hpp>
#include "Controller.h"

class Application
{
public:
    Application();
    Application(int paramScene);
    ~Application();
    void run();

private:
    Window *window;
};