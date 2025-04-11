#include "Scene11.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene11::Scene11()
    : SceneBase(new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene11::draw()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Plain
    shapes->at(0)->addTransformation(new Scale2(50.0f, 0.0f, 50.0f));

    // House
    shapes->at(1)->addTransformation(new Translation(20.0f, 0.0f, 0.0f));

    // Dino
    glm::vec3 bezierPoint = this->bezierCurve->getPoint();
    shapes->at(2)->addTransformation(new Scale2(0.07f, 0.07f, 0.07f));
    shapes->at(2)->addTransformation(new Translation(bezierPoint.x, bezierPoint.y, bezierPoint.z));
    shapes->at(2)->addTransformation(new Rotation(30.0f, 1.0f, 0.0f, 0.0f));

    // Snowman
    shapes->at(3)->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));
    shapes->at(3)->addTransformation(new Translation(-20.0f, 2.8f, 25.0f));
    shapes->at(4)->addTransformation(new Scale2(2.0f, 2.0f, 2.0f));
    shapes->at(4)->addTransformation(new Translation(-20.0f, 7.5f, 25.0f));
    shapes->at(5)->addTransformation(new Translation(-20.0f, 10.0f, 25.0f));

    // Zombie 1
    shapes->at(6)->addTransformation(new Translation(-12.0f, 0.0f, 30.0f));

    // Zombie 2
    shapes->at(7)->addTransformation(new Translation(-7.0f, 0.0f, -15.0f));

    for (int i = 0; i < shapes->size(); i++)
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
}

void Scene11::createShaders()
{
    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // 0
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");                 // 1
    shaderManager->addShaderProgram(camera, "simple_vertex.glsl", "simple_fragment.glsl");                          // 2
}

void Scene11::createShapes()
{
    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(0));
    plainObj->addTexture(textureManager->getTexture(0));
    shapes->push_back(plainObj);

    DrawableModel *houseAssimpObj = new DrawableModel(new AssimpDrawableModel("house_model/house.obj"), shaderManager->getShaderProgram(0));
    houseAssimpObj->addTexture(textureManager->getTexture(2));
    shapes->push_back(houseAssimpObj);

    DrawableModel *dinoAssimpObj1 = new DrawableModel(new AssimpDrawableModel("dino_model/dino.obj"), shaderManager->getShaderProgram(0));
    dinoAssimpObj1->addTexture(textureManager->getTexture(3));
    shapes->push_back(dinoAssimpObj1);

    DrawableModel *sphereObj1 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(1));
    shapes->push_back(sphereObj1);

    DrawableModel *sphereObj2 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(1));
    shapes->push_back(sphereObj2);

    DrawableModel *sphereObj3 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(1));
    shapes->push_back(sphereObj3);

    DrawableModel *zombieAssimpObj1 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(0));
    zombieAssimpObj1->addTexture(textureManager->getTexture(4));
    shapes->push_back(zombieAssimpObj1);

    DrawableModel *zombieAssimpObj2 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(0));
    zombieAssimpObj2->addTexture(textureManager->getTexture(4));
    shapes->push_back(zombieAssimpObj2);

    DrawableModel *crossHairObj = new DrawableModel(new CrossHairModel(), shaderManager->getShaderProgram(2));
    shapes->push_back(crossHairObj);
}

void Scene11::createTextures()
{
    textureManager->addTexture(new Texture2D("grass.png"));                     // 0
    textureManager->addTexture(new Texture2D("tree_model/tree.png"), false);    // 1
    textureManager->addTexture(new Texture2D("house_model/house.png"), true);   // 2
    textureManager->addTexture(new Texture2D("dino_model/dino.jpg"), true);     // 3
    textureManager->addTexture(new Texture2D("zombie_model/zombie.png"), true); // 4
}

void Scene11::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    glm::vec3 pos = glm::unProject(objPosition, camera->getViewMatrix(), camera->getProjectionMatrix(), viewPort);

    DrawableModel *newTree = new DrawableModel(new AssimpDrawableModel("tree_model/tree.obj"), shaderManager->getShaderProgram(0));
    newTree->addTexture(this->textureManager->getTexture(1));
    newTree->addTransformation(new Scale2(0.1f, 0.1f, 0.1f));
    newTree->addTransformation(new Translation(pos.x, 0.0f, pos.z)); // Y = 0, ground level
    shapes->push_back(newTree);
}

void Scene11::removeObjOnClick(int stencilId)
{
    if (stencilId < 0)
    {
        return;
    }

    shapes->at(stencilId)->isVisible = false;
}