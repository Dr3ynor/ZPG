//
// Created by jakub on 29.10.23.
//

#ifndef TEST3_SCENE1_H
#define TEST3_SCENE1_H

#include "DrawableModel.h"
#include "Shader.h"
#include "vector"
#include "Controller.h"
#include "memory"
#include "Camera.h"
#include "CompositeTransform.h"
#include "Scale.h"
#include "SceneBase.h"
#include "SphereModel.h"

class Scene1 : public SceneBase
{
public:
    Scene1();
    ~Scene1() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);
};

#endif // TEST3_SCENE1_H
