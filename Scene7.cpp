#include "Scene7.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene7::Scene7()
    : SceneBase(new Camera())
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene7::draw()
{
    glDepthFunc(GL_LEQUAL); // Make sure the skybox is drawn behind everything
    shapes->at(0)->drawSkybox();
    glDepthFunc(GL_LESS); // Reset depth function
    glClear(GL_DEPTH_BUFFER_BIT);

    for (int i = 1; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }
}

void Scene7::createShaders()
{
    // Shader *shaderProgramSkybox = new Shader(camera, lightManager, "skybox_vertex.glsl", "skybox_fragment.glsl");
    // shaders->push_back(shaderProgramSkybox);

    // Shader *shaderProgramPhong = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
    // shaders->push_back(shaderProgramPhong);

    // Shader *shaderProgramPhongTexture = new Shader(camera, lightManager, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // Phong with textures
    // shaders->push_back(shaderProgramPhongTexture);

    shaderManager->addShaderProgram(camera, "skybox_vertex.glsl", "skybox_fragment.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl");
}

void Scene7::createShapes()
{
    DrawableModel *skybox = new DrawableModel(new SkycubeModel(), shaderManager->getShaderProgram(0));
    skybox->addTexture(textureManager->getTexture(0));
    skybox->updateTexture("textureSampler", skybox->textures[0]->position);
    shapes->push_back(skybox);

    DrawableModel *treeObj1 = new DrawableModel(new TreeModel(), shaderManager->getShaderProgram(1));
    treeObj1->addTransformation(new Translation(5.0f, -1.0f, 0.0f));
    shapes->push_back(treeObj1);

    DrawableModel *giftObj1 = new DrawableModel(new GiftModel(), shaderManager->getShaderProgram(1));
    shapes->push_back(giftObj1);

    // Set plain object
    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(2));
    plainObj->addTexture(textureManager->getTexture(1));
    plainObj->updateTexture("textureSampler", plainObj->textures[0]->position);
    shapes->push_back(plainObj);
}

void Scene7::createTextures()
{
    textureManager->addTexture(new TextureCube("cube_posy.jpg", "cube_negy.jpg", "cube_posz.jpg", "cube_negz.jpg", "cube_posx.jpg", "cube_negx.jpg"));
    textureManager->addTexture(new Texture2D("grass.png"));
}

void Scene7::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene7::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}