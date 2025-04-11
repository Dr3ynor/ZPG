//
// Created by jakub on 29.10.23.
//

#include "Scene5.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene5::Scene5()
    : SceneBase(new Camera())
{
    createShaders();
    createTextures();
    createShapes();

    srand((unsigned int)time(NULL));
}

void Scene5::draw()
{
    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }
}

void Scene5::createShaders()
{
    // Shader *shaderProgramBlinn = new Shader(camera, lightManager, "blinn_vertex.glsl", "blinn_fragment.glsl"); // Blinn
    // shaders->push_back(shaderProgramBlinn);

    // Shader *shaderProgramPhong = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl"); // Phong
    // shaders->push_back(shaderProgramPhong);

    // shaderManager->addShaderProgram(camera, "blinn_vertex.glsl", "blinn_fragmentblinn_fragment.glsl");

    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
}

void Scene5::createShapes()
{
    float scaleX = 50.0f;
    float scaleZ = 50.0f;

    DrawableModel *plainObj = new DrawableModel(new PlainModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(plainObj);
    shapes->at(0)->addTransformation(new Scale2(scaleX, 0.0, scaleZ));

    for (int i = 1; i < 101; i++)
    {
        DrawableModel *randomObj;
        int randomModel = rand() % 5; // tree, bushes, sphere, Suzi, gift
        if (randomModel == 0)
        {
            randomObj = new DrawableModel(new TreeModel(), shaderManager->getShaderProgram(0));
        }
        else if (randomModel == 1)
        {
            randomObj = new DrawableModel(new BushModel(), shaderManager->getShaderProgram(0));
        }
        else if (randomModel == 2)
        {
            randomObj = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
        }
        else if (randomModel == 3)
        {
            randomObj = new DrawableModel(new SuziSmoothModel(), shaderManager->getShaderProgram(0));
        }
        else if (randomModel == 4)
        {
            randomObj = new DrawableModel(new GiftModel(), shaderManager->getShaderProgram(0));
        }

        shapes->push_back(randomObj);

        // Random scale
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f;
        shapes->at(i)->addTransformation(new Scale2(randomScale, randomScale, randomScale));

        // Random position
        float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (scaleX + scaleZ) - ((scaleX + scaleZ) / 2);
        float randomZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (scaleX + scaleZ) - ((scaleX + scaleZ) / 2);
        shapes->at(i)->addTransformation(new Translation(randomX, 0.0f, randomZ));

        // Fix Y
        if (randomModel == 0) // tree
        {
        }
        else if (randomModel == 1) // bushes
        {
        }
        else if (randomModel == 2) // sphere
        {
            shapes->at(i)->addTransformation(new Translation(0.0f, 1.0f, 0.0f));
        }
        else if (randomModel == 3) // suziSmooth
        {
            shapes->at(i)->addTransformation(new Translation(0.0f, 1.3f, 0.0f));
        }
        else if (randomModel == 4) // gift
        {
        }
    }
}

void Scene5::createTextures()
{
    // TODO: impl if needed
}

void Scene5::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene5::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}