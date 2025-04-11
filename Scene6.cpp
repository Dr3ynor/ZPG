#include "Scene6.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene6::Scene6()
    : SceneBase(new Camera())
{
    createShaders();
    createTextures();
    createShapes();

    srand((unsigned int)time(NULL));
}

void Scene6::draw()
{
    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }
}

void Scene6::createShaders()
{
    // Shader *shaderProgramPhongTexture = new Shader(camera, lightManager, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // Phong with textures
    // shaders->push_back(shaderProgramPhongTexture);

    // Shader *shaderProgramPhong = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl"); // Phong
    // shaders->push_back(shaderProgramPhong);

    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
}

void Scene6::createShapes()
{
    // Set plain object
    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(0));
    plainObj->addTexture(textureManager->getTexture(0));
    plainObj->updateTexture("textureSampler", plainObj->textures[0]->position);
    shapes->push_back(plainObj);

    // Set other objects
    DrawableModel *treeObj1 = new DrawableModel(new TreeModel(), shaderManager->getShaderProgram(1));
    treeObj1->addTransformation(new Scale2(0.2f, 0.2f, 0.2f));
    treeObj1->addTransformation(new Translation(1.0f, 0.0f, 0.0f));
    shapes->push_back(treeObj1);

    DrawableModel *treeObj2 = new DrawableModel(new TreeModel(), shaderManager->getShaderProgram(1));
    treeObj2->addTransformation(new Translation(-4.0f, 0.0f, 7.0f));
    shapes->push_back(treeObj2);

    DrawableModel *treeObj3 = new DrawableModel(new TreeModel(), shaderManager->getShaderProgram(1));
    treeObj3->addTransformation(new Translation(-8.0f, 0.0f, -1.0f));
    shapes->push_back(treeObj3);

    DrawableModel *giftObj1 = new DrawableModel(new GiftModel(), shaderManager->getShaderProgram(1));
    giftObj1->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));
    giftObj1->addTransformation(new Translation(-3.0f, 0.0f, -6.0f));
    shapes->push_back(giftObj1);
}

void Scene6::createTextures()
{
    textureManager->addTexture(new Texture2D("grass.png"));
}

void Scene6::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene6::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}