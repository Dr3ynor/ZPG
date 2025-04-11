//
// Created by jakub on 3.10.23.
//

#ifndef TEST3_WINDOW_H
#define TEST3_WINDOW_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "SceneBase.h"
#include "Scene1.h"
#include "vector"
#include "SceneFactory.h"

class Window
{
public:
    Window();
    Window(int paramScene);
    ~Window();
    GLFWwindow *getWindow();
    SceneBase *scene;

    bool mouseLock;
    bool mouseInit;
    float mouseX;
    float mouseY;
    void setMouseXY(float x, float y);

private:
    static void error_callback(int error, const char *description);

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void window_focus_callback(GLFWwindow *window, int focused);

    static void window_iconify_callback(GLFWwindow *window, int iconified);

    static void window_size_callback(GLFWwindow *window, int width, int height);

    static void cursor_callback(GLFWwindow *window, double x, double y);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mode);

    GLFWwindow *window;
    void createWindow();
    void runFunctions();

    SceneFactory *sceneFactory;
};

#endif // TEST3_WINDOW_H
