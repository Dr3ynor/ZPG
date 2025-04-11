#include "Scene10.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

//   new Camera(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(-10.0f, -10.0f, 0.0f)))

Scene10::Scene10()
    : SceneBase(new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene10::draw()
{
    glDepthFunc(GL_LEQUAL); // Make sure the skybox is drawn behind everything
    shapes->at(0)->drawSkybox();
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glDepthFunc(GL_LESS); // Reset depth function
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Plain
    shapes->at(1)->addTransformation(new Scale2(50.0f, 0.0f, 50.0f));

    // House
    shapes->at(2)->addTransformation(new Translation(20.0f, 0.0f, 0.0f));

    // Dino
    glm::vec3 bezierPoint = this->bezierCurve->getPoint();
    shapes->at(3)->addTransformation(new Scale2(0.07f, 0.07f, 0.07f));
    shapes->at(3)->addTransformation(new Translation(bezierPoint.x, bezierPoint.y, bezierPoint.z));
    shapes->at(3)->addTransformation(new Rotation(30.0f, 1.0f, 0.0f, 0.0f));

    // Snowman
    shapes->at(4)->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));
    shapes->at(4)->addTransformation(new Translation(-20.0f, 2.8f, 25.0f));
    shapes->at(5)->addTransformation(new Scale2(2.0f, 2.0f, 2.0f));
    shapes->at(5)->addTransformation(new Translation(-20.0f, 7.5f, 25.0f));
    shapes->at(6)->addTransformation(new Translation(-20.0f, 10.0f, 25.0f));

    // Zombie 1
    shapes->at(7)->addTransformation(new Translation(-12.0f, 0.0f, 30.0f));

    // Zombie 2
    shapes->at(8)->addTransformation(new Translation(-7.0f, 0.0f, -15.0f));

    for (int i = 1; i < shapes->size(); i++)
    {
        glStencilFunc(GL_ALWAYS, i, 0xFF);

        if (!shapes->at(i)->isVisible)
        {
            continue;
        }

        switch (shapes->at(i)->textures.size())
        {
        case 0:
            shapes->at(i)->draw();
            break;
        case 1:
            shapes->at(i)->updateTexture("textureSampler", shapes->at(i)->textures[0]->position);
            shapes->at(i)->draw();
            break;
        default:
            continue;
        }
    }

    shapes->at(0)->clearTransformations();
    shapes->at(1)->clearTransformations();
    shapes->at(2)->clearTransformations();
    shapes->at(3)->clearTransformations();
    shapes->at(4)->clearTransformations();
    shapes->at(5)->clearTransformations();
    shapes->at(6)->clearTransformations();
    shapes->at(7)->clearTransformations();
    shapes->at(8)->clearTransformations();
}

void Scene10::createShaders()
{
    shaderManager->addShaderProgram(camera, "skybox_vertex.glsl", "skybox_fragment.glsl");                          // 0
    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // 1
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");                 // 2
    shaderManager->addShaderProgram(camera, "simple_vertex.glsl", "simple_fragment.glsl");                          // 3
}

void Scene10::createShapes()
{
    DrawableModel *skybox = new DrawableModel(new SkycubeModel(), shaderManager->getShaderProgram(0));
    skybox->addTexture(textureManager->getTexture(0));
    skybox->updateTexture("textureSampler", skybox->textures[0]->position);
    shapes->push_back(skybox);

    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(1));
    plainObj->addTexture(textureManager->getTexture(1));
    shapes->push_back(plainObj);

    DrawableModel *houseAssimpObj = new DrawableModel(new AssimpDrawableModel("house_model/house.obj"), shaderManager->getShaderProgram(1));
    houseAssimpObj->addTexture(textureManager->getTexture(3));
    shapes->push_back(houseAssimpObj);

    DrawableModel *dinoAssimpObj1 = new DrawableModel(new AssimpDrawableModel("dino_model/dino.obj"), shaderManager->getShaderProgram(1));
    dinoAssimpObj1->addTexture(textureManager->getTexture(4));
    shapes->push_back(dinoAssimpObj1);

    DrawableModel *sphereObj1 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(2));
    shapes->push_back(sphereObj1);

    DrawableModel *sphereObj2 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(2));
    shapes->push_back(sphereObj2);

    DrawableModel *sphereObj3 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(2));
    shapes->push_back(sphereObj3);

    DrawableModel *crossHairObj = new DrawableModel(new CrossHairModel(), shaderManager->getShaderProgram(3));
    shapes->push_back(crossHairObj);

    DrawableModel *zombieAssimpObj1 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(1));
    zombieAssimpObj1->addTexture(textureManager->getTexture(5));
    shapes->push_back(zombieAssimpObj1);

    DrawableModel *zombieAssimpObj2 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(1));
    zombieAssimpObj2->addTexture(textureManager->getTexture(5));
    shapes->push_back(zombieAssimpObj2);
}

void Scene10::createTextures()
{
    textureManager->addTexture(new TextureCube("cube_posy.jpg", "cube_negy.jpg", "cube_posz.jpg", "cube_negz.jpg", "cube_posx.jpg", "cube_negx.jpg")); // 0
    textureManager->addTexture(new Texture2D("grass.png"));                                                                                            // 1
    textureManager->addTexture(new Texture2D("tree_model/tree.png"));                                                                                  // 2
    textureManager->addTexture(new Texture2D("house_model/house.png"), true);                                                                          // 3
    textureManager->addTexture(new Texture2D("dino_model/dino.jpg"), true);                                                                            // 4
    textureManager->addTexture(new Texture2D("zombie_model/zombie.png"), true);                                                                        // 5
}

void Scene10::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    glm::vec3 pos = glm::unProject(objPosition, camera->getViewMatrix(), camera->getProjectionMatrix(), viewPort);

    DrawableModel *newTree = new DrawableModel(new AssimpDrawableModel("tree_model/tree.obj"), shaderManager->getShaderProgram(1));
    newTree->addTexture(this->textureManager->getTexture(2));
    newTree->addTransformation(new Scale2(0.1f, 0.1f, 0.1f));
    newTree->addTransformation(new Translation(pos.x, 0.0f, pos.z)); // Y = 0, ground level
    this->shapes->push_back(newTree);
}

void Scene10::removeObjOnClick(int stencilId)
{
    if (stencilId < 0)
    {
        return;
    }

    shapes->at(stencilId)->isVisible = false;
}