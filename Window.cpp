//
// Created by jakub on 3.10.23.
//

#include "Window.h"
#include <iostream>
#include <cstdio>

Window::Window()
{
    createWindow();
    runFunctions();

    mouseInit = true;

    Scene1 *scene1 = new Scene1();
    scene1->lightManager->addPointLight(new PointLight(glm::vec3(10.0f, 1.0f, 2.0f), 1.0f, 0.0f, 0.001f));

    this->scene = scene1;
}

Window::Window(int paramScene)
{
    createWindow();
    runFunctions();

    mouseInit = true;
    sceneFactory = new SceneFactory();

    this->scene = sceneFactory->getScene(paramScene);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Window::getWindow()
{
    return this->window;
}

void Window::createWindow()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    // glViewport(0, 0, width, height);

    glfwSetWindowUserPointer(window, this);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::runFunctions()
{
    // Sets the key callback
    glfwSetKeyCallback(window, key_callback);

    glfwSetCursorPosCallback(window, cursor_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwSetWindowIconifyCallback(window, window_iconify_callback);

    glfwSetWindowSizeCallback(window, window_size_callback);
}

void Window::error_callback(int error, const char *description) { fputs(description, stderr); }

void Window::window_focus_callback(GLFWwindow *window, int focused) { printf("window_focus_callback \n"); }

void Window::window_iconify_callback(GLFWwindow *window, int iconified) { printf("window_iconify_callback \n"); }

void Window::window_size_callback(GLFWwindow *window, int width, int height)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    w->scene->camera->setWidthAndHeight(width, height);

    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Window::cursor_callback(GLFWwindow *window, double x, double y)
{
    printf("X: %lf, Y: %lf\n", x, y);
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->mouseInit)
    {
        w->setMouseXY(x, y);
        w->mouseInit = false;
        w->scene->cursorCallBack(x, y);
        return;
    }

    float xTemp = x - w->mouseX;
    float yTemp = w->mouseY - y;
    w->setMouseXY(x, y);

    w->scene->cursorCallBack(xTemp, yTemp);
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    printf("key_callback: KEY: %d, SCANCODE: %d, ACTION: %d, MODE: %d\n", key, scancode, action, mode);

    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
    w->scene->notify(key);

    // key "L" toggles mouse lock for given window
    if (action == GLFW_PRESS && key == GLFW_KEY_L)
    {
        w->mouseLock = !w->mouseLock;
        printf("Mouse lock: %d\n", w->mouseLock);

        if (w->mouseLock)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    // key "G" toggles gravity mode
    if (action == GLFW_PRESS && key == GLFW_KEY_G)
    {
        w->scene->camera->gravityOn = !w->scene->camera->gravityOn;
        printf("Gravity ON: %d\n", w->scene->camera->gravityOn);
    }
}

// mouse button callback
void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    // adding object
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        GLfloat depth;
        int _x = width / 2;
        int _y = height / 2;
        glReadPixels(_x, _y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

        glm::vec3 spawnObjectPosition = glm::vec3(_x, _y, depth);
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glm::vec4 viewPort = glm::vec4(0, 0, windowWidth, windowHeight);

        w->scene->addObjOnClick(spawnObjectPosition, viewPort);

        printf("Object added to position [%f %f %f]\n", spawnObjectPosition.x, spawnObjectPosition.y, spawnObjectPosition.z);
        printf("Depth: %f\n", depth);
    }

    // identification, remove object
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        int _x = width / 2 + 1; // +1 pixel because of the crosshair (if present in scene)
        int _y = height / 2 + 1;

        GLuint index;
        glReadPixels(_x, _y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        GLfloat depth;
        glReadPixels(_x, _y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        GLbyte color[4];
        glReadPixels(_x, _y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

        w->scene->removeObjOnClick(index);

        printf("Stencil ID: %d\n", index);
        printf("Depth: %f\n", depth);
        printf("Color %02hhx%02hhx%02hhx%02hhx\n", color[0], color[1], color[2], color[3]);
    }
}

void Window::setMouseXY(float x, float y)
{
    this->mouseX = x;
    this->mouseY = y;
}
