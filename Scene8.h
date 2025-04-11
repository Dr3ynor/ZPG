#ifndef TEST3_SCENE8_H
#define TEST3_SCENE8_H

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
#include "GiftModel.h"
#include "PlainTextureModel.h"
#include "AssimpDrawableModel.h"

class Scene8 : public SceneBase
{
public:
    Scene8();
    ~Scene8() = default;

    void createShaders();
    void createShapes();
    void createTextures();

    void draw();
    void addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort);
    void removeObjOnClick(int stencilId);
};

#endif // TEST3_SCENE8_H
