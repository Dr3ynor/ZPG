//
// Created by jakub on 29.10.23.
//

#include "Scene4.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene4::Scene4()
    : SceneBase(new Camera())
{
    createShaders();
    createTextures();
    createShapes();
}

void Scene4::draw()
{
    shapes->at(1)->addTransformation(new Translation(5.0f, 0.0, 0.0f));

    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }

    shapes->at(1)->clearTransformations();
}

void Scene4::createShaders()
{
    // Shader *shaderProgram = new Shader(camera, lightManager, "blinn_vertex.glsl", "blinn_fragment.glsl"); // Blinn
    // shaders->push_back(shaderProgram);

    shaderManager->addShaderProgram(camera, "blinn_vertex.glsl", "blinn_fragment.glsl");
}

void Scene4::createShapes()
{
    DrawableModel *sphereObj = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sphereObj);

    DrawableModel *suziObj = new DrawableModel(new SuziSmoothModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(suziObj);
}

void Scene4::createTextures()
{
    // TODO: impl if needed
}

void Scene4::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene4::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}