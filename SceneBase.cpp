//
// Created by jakub on 20.10.23.
//

#include "SceneBase.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"
#include "sphere.h"
#include "suzi_smooth.h"

SceneBase::SceneBase(Camera *camera)
{
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    this->camera = camera;
    this->lightManager = new LightManager();
    this->textureManager = new TextureManager();
    this->shaderManager = new ShaderManager(lightManager);
    this->controller = new Controller();

    this->compositeTransform = std::make_unique<CompositeTransform>();
    this->shapes = new std::vector<DrawableModel *>();

    glm::mat4x3 bezierMatrix = glm::mat4x3(glm::vec3(0.0f, 0.0f, 5.0f),
                                           glm::vec3(-16.0f, 0.0f, 5.0f),
                                           glm::vec3(5.0f, 0.0f, 10.0f),
                                           glm::vec3(-10.0f, 0.0f, 10.0f));

    this->bezierCurve = new BezierCurve(bezierMatrix);
}

SceneBase::~SceneBase()
{
    for (auto &shape : *shapes)
    {
        delete shape;
    }
}

void SceneBase::notify(int k)
{
    camera->changeCamera(k);
}

void SceneBase::cursorCallBack(float x, float y)
{
    camera->cursorCallback(x, y);
}
