#include "Scene9.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene9::Scene9()
    : SceneBase(new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene9::draw()
{
    glDepthFunc(GL_LEQUAL); // Make sure the skybox is drawn behind everything
    shapes->at(0)->drawSkybox();
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glDepthFunc(GL_LESS); // Reset depth function
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
}

void Scene9::createShaders()
{
    // Shader *shaderProgramSkybox = new Shader(camera, lightManager, "skybox_vertex.glsl", "skybox_fragment.glsl"); // 0  Skybox shaders
    // shaders->push_back(shaderProgramSkybox);

    // Shader *shaderProgramPhongTexture = new Shader(camera, lightManager, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl"); // 1  Phong with textures multilight support
    // shaders->push_back(shaderProgramPhongTexture);

    shaderManager->addShaderProgram(camera, "skybox_vertex.glsl", "skybox_fragment.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex_texture.glsl", "phong_fragment_multilight_texture.glsl");
}

void Scene9::createShapes()
{
    DrawableModel *skybox = new DrawableModel(new SkycubeModel(), shaderManager->getShaderProgram(0));
    skybox->addTexture(textureManager->getTexture(0));
    skybox->updateTexture("textureSampler", skybox->textures[0]->position);
    shapes->push_back(skybox);

    DrawableModel *plainObj = new DrawableModel(new PlainTextureModel(), shaderManager->getShaderProgram(1));
    plainObj->addTransformation(new Scale2(50.0f, 0.0f, 50.0f));
    plainObj->addTexture(textureManager->getTexture(1));
    shapes->push_back(plainObj);
}

void Scene9::createTextures()
{
    textureManager->addTexture(new TextureCube("cube_posy.jpg", "cube_negy.jpg", "cube_posz.jpg", "cube_negz.jpg", "cube_posx.jpg", "cube_negx.jpg")); // 0
    textureManager->addTexture(new Texture2D("grass.png"));                                                                                            // 1
    textureManager->addTexture(new Texture2D("tree_model/tree.png"));                                                                                  // 2
}

void Scene9::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene9::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}