//
// Created by jakub on 29.10.23.
//

#include "Scene1.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene1::Scene1()
    : SceneBase(
          new Camera(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(-10.0f, -10.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene1::draw()
{
    shapes->at(0)->addTransformation(new Translation(-2.0f, 0.0f, 0.0f));
    shapes->at(1)->addTransformation(new Translation(2.0f, 0.0f, 0.0f));

    shapes->at(2)->addTransformation(new Translation(0.0f, 2.0f, 0.0f));
    shapes->at(3)->addTransformation(new Translation(0.0f, -2.0f, 0.0f));

    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }

    shapes->at(0)->clearTransformations();
    shapes->at(1)->clearTransformations();
    shapes->at(2)->clearTransformations();
    shapes->at(3)->clearTransformations();
}

void Scene1::createShaders()
{
    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");

    // Shader *shaderProgram = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl"); // Phong
    // shaders->push_back(shaderProgram);
}

void Scene1::createShapes()
{
    DrawableModel *sphereObj1 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj1);

    DrawableModel *sphereObj2 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj2);

    DrawableModel *sphereObj3 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj3);

    DrawableModel *sphereObj4 = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj4);
}

void Scene1::createTextures()
{
    // TODO: impl if needed
}

void Scene1::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene1::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}