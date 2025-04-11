//
// Created by jakub on 29.10.23.
//

#ifndef TEST3_SCENE3_H
#define TEST3_SCENE3_H

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

class Scene3 : public SceneBase
{
public:
    Scene3();
    ~Scene3() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);

private:
    float rotationAngle = 0.05f;
};

#endif // TEST3_SCENE3_H
