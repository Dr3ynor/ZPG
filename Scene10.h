#ifndef TEST3_SCENE10_H
#define TEST3_SCENE10_H

#include "DrawableModel.h"
#include "Shader.h"
#include "vector"
#include "Controller.h"
#include "memory"
#include "Camera.h"
#include "CompositeTransform.h"
#include "Scale.h"
#include "SceneBase.h"
#include "SkycubeModel.h"
#include "TreeModel.h"
#include "SphereModel.h"
#include "CrossHairModel.h"
#include "PlainTextureModel.h"
#include "AssimpDrawableModel.h"

class Scene10 : public SceneBase
{
public:
    Scene10();
    ~Scene10() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);
};

#endif // TEST3_SCENE10_H
