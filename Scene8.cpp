#include "Scene8.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene8::Scene8()
    : SceneBase(new Camera(glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene8::draw()
{
    // glDepthFunc(GL_LEQUAL); // Make sure the skybox is drawn behind everything
    // shapes->at(0)->drawSkybox();
    // glDepthFunc(GL_LESS); // Reset depth function
    // glClear(GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < shapes->size(); i++)
    {
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
}

void Scene8::createShaders()
{
    // Shader *shaderProgramSkybox = new Shader(camera, lightManager, "skybox_vertex.glsl", "skybox_fragment.glsl"); // 0  Skybox shaders
    // shaders->push_back(shaderProgramSkybox);

    // Shader *shaderProgramPhongTexture = new Shader(camera, lightManager, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // 1  Phong with textures multilight support
    // shaders->push_back(shaderProgramPhongTexture);

    shaderManager->addShaderProgram(camera, "skybox_vertex.glsl", "skybox_fragment.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl");
}

void Scene8::createShapes()
{
    // DrawableModel *skybox = new DrawableModel(new SkycubeModel(), shaderManager->getShaderProgram(0));
    // skybox->addTexture(textureManager->getTexture(0));
    // skybox->updateTexture("textureSampler", skybox->textures[0]->position);
    // shapes->push_back(skybox);

    // Set plain object
    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(1));
    plainObj->addTransformation(new Scale2(30.0f, 0.0f, 30.0f));
    plainObj->addTexture(textureManager->getTexture(1));
    shapes->push_back(plainObj);

    // Assimp lib loaded models
    DrawableModel *houseAssimpObj = new DrawableModel(new AssimpDrawableModel("house_model/house.obj"), shaderManager->getShaderProgram(1));
    houseAssimpObj->addTexture(textureManager->getTexture(2));
    shapes->push_back(houseAssimpObj);

    DrawableModel *treeAssimpObj1 = new DrawableModel(new AssimpDrawableModel("tree_model/tree.obj"), shaderManager->getShaderProgram(1));
    treeAssimpObj1->addTransformation(new Translation(5.0f, 0.0f, 12.0f));
    treeAssimpObj1->addTexture(textureManager->getTexture(3));
    shapes->push_back(treeAssimpObj1);

    DrawableModel *treeAssimpObj2 = new DrawableModel(new AssimpDrawableModel("tree_model/tree.obj"), shaderManager->getShaderProgram(1));
    treeAssimpObj2->addTransformation(new Scale2(0.3f, 0.3f, 0.3f));
    treeAssimpObj2->addTransformation(new Translation(15.0f, 0.0f, 8.0f));
    treeAssimpObj2->addTexture(textureManager->getTexture(3));
    shapes->push_back(treeAssimpObj2);

    DrawableModel *treeAssimpObj3 = new DrawableModel(new AssimpDrawableModel("tree_model/tree.obj"), shaderManager->getShaderProgram(1));
    treeAssimpObj3->addTransformation(new Scale2(0.5f, 0.5f, 0.5f));
    treeAssimpObj3->addTransformation(new Translation(25.0f, 0.0f, 20.0f));
    treeAssimpObj3->addTexture(textureManager->getTexture(3));
    shapes->push_back(treeAssimpObj3);

    DrawableModel *zombieAssimpObj1 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(1));
    zombieAssimpObj1->addTransformation(new Translation(10.0f, 0.0f, 19.0f));
    zombieAssimpObj1->addTexture(textureManager->getTexture(4));
    shapes->push_back(zombieAssimpObj1);

    DrawableModel *zombieAssimpObj2 = new DrawableModel(new AssimpDrawableModel("zombie_model/zombie.obj"), shaderManager->getShaderProgram(1));
    zombieAssimpObj2->addTransformation(new Translation(9.0f, 0.0f, 2.0f));
    zombieAssimpObj2->addTexture(textureManager->getTexture(4));
    shapes->push_back(zombieAssimpObj2);

    DrawableModel *dinoAssimpObj1 = new DrawableModel(new AssimpDrawableModel("dino_model/dino.obj"), shaderManager->getShaderProgram(1));
    dinoAssimpObj1->addTransformation(new Scale2(0.09f, 0.09f, 0.09f));
    dinoAssimpObj1->addTransformation(new Translation(9.0f, 20.0f, 2.0f));
    dinoAssimpObj1->addTransformation(new Rotation(30.0f, 1.0f, 0.0f, 0.0f));
    dinoAssimpObj1->addTexture(textureManager->getTexture(5));
    shapes->push_back(dinoAssimpObj1);
}

void Scene8::createTextures()
{
    textureManager->addTexture(new TextureCube("cube_posy.jpg", "cube_negy.jpg", "cube_posz.jpg", "cube_negz.jpg", "cube_posx.jpg", "cube_negx.jpg")); // 0
    textureManager->addTexture(new Texture2D("grass.png"), true);                                                                                      // 1
    textureManager->addTexture(new Texture2D("house_model/house.png"));                                                                                // 2
    textureManager->addTexture(new Texture2D("tree_model/tree.png"));                                                                                  // 3
    textureManager->addTexture(new Texture2D("zombie_model/zombie.png"));                                                                              // 4
    textureManager->addTexture(new Texture2D("dino_model/dino.jpg"));                                                                                  // 5
}

void Scene8::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene8::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}