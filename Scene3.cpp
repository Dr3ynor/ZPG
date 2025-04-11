//
// Created by jakub on 29.10.23.
//

#include "Scene3.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene3::Scene3()
    : SceneBase(
          new Camera(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene3::draw()
{
    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }
}

void Scene3::createShaders()
{
    // Shader *shaderProgram = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment.glsl"); // Phong
    // shaders->push_back(shaderProgram);

    // Shader *shaderProgramWrong = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_wrong.glsl"); // Phong wrong
    // shaders->push_back(shaderProgramWrong);

    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment.glsl");
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_wrong.glsl");
}

void Scene3::createShapes()
{
    DrawableModel *sphereObj = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj);
}

void Scene3::createTextures()
{
    // TODO: impl if needed
}

void Scene3::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene3::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}