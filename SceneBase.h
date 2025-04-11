//
// Created by jakub on 20.10.23.
//

#ifndef TEST3_SCENE_H
#define TEST3_SCENE_H

#include "DrawableModel.h"
#include "Shader.h"
#include "vector"
#include "Controller.h"
#include "memory"
#include "Camera.h"
#include "CompositeTransform.h"
#include "Scale.h"
#include "LightManager.h"
#include "TextureManager.h"
#include "TreeModel.h"
#include "AssimpDrawableModel.h"
#include "BezierCurve.h"
#include "ShaderManager.h"

class SceneBase
{
public:
    SceneBase(Camera *camera);
    ~SceneBase();

    Camera *camera;
    LightManager *lightManager;
    TextureManager *textureManager;
    ShaderManager *shaderManager;
    std::vector<DrawableModel *> *shapes;
    DrawableModel *skybox;
    std::unique_ptr<CompositeTransform> compositeTransform;
    Controller *controller;

    void notify(int k);
    void cursorCallBack(float x, float y);

    virtual void createShaders() = 0;
    virtual void createShapes() = 0;
    virtual void createTextures() = 0;
    virtual void draw() = 0;
    virtual void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort) = 0;
    virtual void removeObjOnClick(int stencilId) = 0;

    BezierCurve *bezierCurve;

private:
};

#endif // TEST3_SCENE_H
