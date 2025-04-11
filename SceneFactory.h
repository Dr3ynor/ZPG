#pragma once

#include "SceneBase.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene21.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Scene8.h"
#include "Scene9.h"
#include "Scene10.h"
#include "Scene11.h"

#include "PointLight.h"
#include "SpotLight.h"
#include "SpotLightCamera.h"
#include "DirectionalLight.h"

class SceneFactory
{
public:
    SceneFactory();
    ~SceneFactory();
    SceneBase *getScene(int paramScene);

private:
};
