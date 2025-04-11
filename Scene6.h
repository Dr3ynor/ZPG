//
// Created by jakub on 29.10.23.
//

#ifndef TEST3_SCENE6_H
#define TEST3_SCENE6_H

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
#include "SuziSmoothModel.h"
#include "PlainTextureModel.h"
#include "GiftModel.h"
#include "BushModel.h"
#include "TreeModel.h"

class Scene6 : public SceneBase
{
public:
    Scene6();
    ~Scene6() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);
};

#endif // TEST3_SCENE6_H
