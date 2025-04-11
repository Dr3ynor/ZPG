//
// Created by jakub on 29.10.23.
//

#ifndef TEST3_SCENE5_H
#define TEST3_SCENE5_H

#include "DrawableModel.h"
#include "Shader.h"
#include "vector"
#include "Controller.h"
#include "memory"
#include "Camera.h"
#include "CompositeTransform.h"
#include "Scale.h"
#include "SceneBase.h"
#include "TreeModel.h"
#include "SphereModel.h"
#include "SuziSmoothModel.h"
#include "BushModel.h"
#include "GiftModel.h"
#include "PlainModel.h"

class Scene5 : public SceneBase
{
public:
    Scene5();
    ~Scene5() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);
};

#endif // TEST3_SCENE5_H
