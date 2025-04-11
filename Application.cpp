#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "memory"

Application::Application()
{
    this->window = new Window();
}

Application::Application(int paramScene)
{
    this->window = new Window(paramScene);
}

Application::~Application() = default;

void Application::run()
{
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window->getWindow()) && glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        window->scene->draw();
        glfwPollEvents();
        glfwSwapBuffers(window->getWindow());
    }
}
