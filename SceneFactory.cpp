
#include "SceneFactory.h"

SceneFactory::SceneFactory()
{
}

SceneFactory::~SceneFactory() = default;

/*
Returns new Scene object, if paramScene not privided, then return Scene1 by default
*/
SceneBase *SceneFactory::getScene(int paramScene)
{
    if (paramScene == 1) // Phong
    {
        Scene1 *scene1 = new Scene1();
        // DONE
        // scene1->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.001f));
        // scene1->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 10.0f, 0.0f), 1.0f, 0.0f, 0.001f));

        // DONE
        scene1->lightManager->addSpotLight(new SpotLight(glm::vec3(0.0f, 5.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f, 0.0f, 0.05f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene1->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.02f, 0.01f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));

        // DONE
        // scene1->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.02f, 0.01f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));

        // DONE
        // scene1->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(-1.0f, -1.0f, 0.0f)));

        return scene1;
    }
    else if (paramScene == 2) // solar system v0
    {
        Scene2 *scene2 = new Scene2();
        scene2->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.02f, 0.01f, glm::vec3(1.0f, 1.0f, 0.0f)));
        scene2->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.01f, 0.01f, 0.05f, glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene2;
    }
    else if (paramScene == 21) // solar system v1
    {
        Scene21 *scene21 = new Scene21();
        scene21->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.02f, 0.01f));

        return scene21;
    }
    else if (paramScene == 3) // sphere light test
    {
        Scene3 *scene3 = new Scene3();
        scene3->lightManager->addPointLight(new PointLight(glm::vec3(10.0f, 1.0f, 2.0f), 1.0f, 0.0f, 0.001f));

        return scene3;
    }
    else if (paramScene == 4) // resize window test
    {
        Scene4 *scene4 = new Scene4();
        scene4->lightManager->addPointLight(new PointLight(glm::vec3(10.0f, 1.0f, 2.0f), 1.0f, 0.0f, 0.001f));

        return scene4;
    }
    else if (paramScene == 5) // forest with presents and monkeys
    {
        Scene5 *scene5 = new Scene5();
        // scene5->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.001f, glm::vec3(1.0f, 1.0f, 1.0f)));
        // scene5->lightManager->addSpotLight(new SpotLight(glm::vec3(0.0f, 5.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f, 0.0f, 0.90f));
        // scene5->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.0f, 0.01f, 0.98f));
        scene5->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(0.0f, 1.0f, 0.0f)));

        return scene5;
    }
    else if (paramScene == 6) // forest with presents and trees on grass texture
    {
        Scene6 *scene6 = new Scene6();

        scene6->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(0.0f, 3.0f, 0.0f)));
        // scene6->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.001f, glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene6;
    }
    else if (paramScene == 7) // skycam
    {
        Scene7 *scene7 = new Scene7();
        // scene7->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.001f, glm::vec3(1.0f, 1.0f, 1.0f)));
        // scene7->lightManager->addSpotLight(new SpotLight(glm::vec3(0.0f, 5.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f, 0.0f, 0.05f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene7->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(0.0f, 2.0f, 0.0f)));
        // scene7->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.02f, 0.01f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene7;
    }
    else if (paramScene == 8) // assimp objects
    {
        Scene8 *scene8 = new Scene8();
        // scene8->lightManager->addPointLight(new PointLight(glm::vec3(-10.0f, 1.0f, -10.0f), 1.0f, 0.0f, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f)));
        // scene8->lightManager->addSpotLight(new SpotLight(glm::vec3(12.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), 1.0f, 0.0f, 0.0f, 0.90f, glm::vec3(1.0f, 1.0f, 1.0f)));
        // scene8->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
        scene8->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.02f, 0.01f, 0.02f, glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene8;
    }
    else if (paramScene == 9) // planting trees
    {
        Scene9 *scene9 = new Scene9();
        scene9->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.01f, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene9;
    }
    else if (paramScene == 10) // bezier curve and final scene, all lights, all models
    {
        Scene10 *scene10 = new Scene10();
        scene10->lightManager->addPointLight(new PointLight(glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.01f, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f)));
        //scene10->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.0f, 0.01f, 0.97f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene10->lightManager->addSpotLight(new SpotLight(glm::vec3(4.0f, -1.0f, 0.0f), glm::vec3(-1.0f, -0.2f, 0.0f), 1.0f, 0.0f, 0.0f, 0.97f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene10->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene10;
    }
    else if (paramScene == 11) // bezier curve and final scene, all lights, no skybox
    {
        Scene11 *scene11 = new Scene11();
        scene11->lightManager->addPointLight(new PointLight(glm::vec3(20.0f, 1.0f, 20.0f), 1.0f, 0.01f, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene11->lightManager->addPointLight(new PointLight(glm::vec3(-40.0f, 1.0f, -40.0f), 1.0f, 0.01f, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene11->lightManager->addSpotLightCameraLight(new SpotLightCamera(1.0f, 0.0f, 0.01f, 0.97f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene11->lightManager->addSpotLight(new SpotLight(glm::vec3(4.0f, -1.0f, 0.0f), glm::vec3(-1.0f, -0.2f, 0.0f), 1.0f, 0.0f, 0.0f, 0.97f, glm::vec3(1.0f, 1.0f, 1.0f)));
        scene11->lightManager->addDirectionalLight(new DirectionalLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

        return scene11;
    }

    // Default scene
    Scene1 *scene = new Scene1();
    scene->lightManager->addPointLight(new PointLight(glm::vec3(10.0f, 1.0f, 2.0f), 1.0f, 0.0f, 0.001f));

    return scene;
}
