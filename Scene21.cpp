//
// Created by jakub on 29.10.23.
//

#include "Scene21.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene21::Scene21()
    : SceneBase(
          new Camera(glm::vec3(-42.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

// 1
// void Scene21::draw()
// {
//     // Sun
//     shapes->at(0)->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));

//     // Earth
//     // Calculate the new rotation matrix for the Earth's orbit
//     Rotation earthRotation(rotationAngle, 0, 1.0f, 0);
//     // Apply the rotation to the Earth's initial position
//     glm::mat4 earthOrbit = earthRotation.getMatrix4();
//     glm::vec3 earthPosition = glm::vec3(5.0f, 0, 0); // Initial position of the Earth relative to Sun
//     glm::vec3 newEarthPosition = glm::vec3(earthOrbit * glm::vec4(earthPosition, 1.0f));
//     shapes->at(1)->addTransformation(new Translation(newEarthPosition.x, newEarthPosition.y, newEarthPosition.z));

//     // Calculate the new rotation matrix for the Moon's orbit
//     Rotation moonRotation(rotationAngle, 0, 1.0f, 0);
//     // Apply the rotation to the Moon's initial position
//     glm::mat4 moonOrbit = moonRotation.getMatrix4();
//     glm::vec3 moonPosition = glm::vec3(newEarthPosition.x, newEarthPosition.y, newEarthPosition.z); // Initial position of the Moon relative to Earth
//     glm::vec3 newMoonPosition = glm::vec3(moonOrbit * glm::vec4(moonPosition, 1.0f));

//     // Moon - Position of the Moon relative to the Earth
//     shapes->at(2)->addTransformation(new Scale2(0.5f, 0.5f, 0.5f));
//     shapes->at(2)->addTransformation(new Translation(newMoonPosition.x, newMoonPosition.y, newMoonPosition.z));

//     for (int i = 0; i < shapes->size(); i++)
//     {
//         shapes->at(i)->draw();
//     }

//     shapes->at(0)->clearTransformations();
//     shapes->at(1)->clearTransformations();
//     shapes->at(2)->clearTransformations();

//     rotationAngle += 0.03f;
// }

// 2
void Scene21::draw()
{
    // Calculate the rotation matrices for the Earth's and Moon's orbits
    Rotation earthRotation(rotationAngle, 0, 1.0f, 0);
    Rotation moonRotation(rotationAngle, 0, 1.0f, 0);

    // Calculate the new positions of the Earth and Moon
    glm::mat4 earthOrbit = earthRotation.getMatrix4();
    glm::vec3 earthPosition = glm::vec3(6.0f, 0, 0); // Initial position of the Earth relative to Sun
    glm::vec3 newEarthPosition = glm::vec3(earthOrbit * glm::vec4(earthPosition, 1.0f));

    glm::mat4 moonOrbit = moonRotation.getMatrix4();
    glm::vec3 moonPosition = glm::vec3(newEarthPosition.x + 2.0, newEarthPosition.y, newEarthPosition.z); // Initial position of the Moon relative to Earth
    glm::vec3 newMoonPosition = glm::vec3(moonOrbit * glm::vec4(moonPosition, 1.0f));

    // Apply transformations to the objects
    // Sun
    shapes->at(0)->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));
    shapes->at(0)->addTransformation(new Translation(0, 0, 0));

    // Earth
    shapes->at(1)->addTransformation(new Translation(newEarthPosition.x, newEarthPosition.y, newEarthPosition.z));

    // Moon
    shapes->at(2)->clearTransformations();
    shapes->at(2)->addTransformation(new Scale2(0.5f, 0.5f, 0.5f));
    shapes->at(2)->addTransformation(new Translation(newMoonPosition.x, newMoonPosition.y, newMoonPosition.z));

    // Render the scene
    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }

    shapes->at(0)->clearTransformations();
    shapes->at(1)->clearTransformations();
    shapes->at(2)->clearTransformations();

    rotationAngle += 0.03f;
}

void Scene21::createShaders()
{
    // Shader *shaderProgram = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl"); // Phong
    // shaders->push_back(shaderProgram);

    // // Shader *shaderProgram2 = new Shader(camera, lightManager, "constant_vertex.glsl", "constant_fragment.glsl");
    // // shaders->push_back(shaderProgram2);

    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
    // shaderManager->addShaderProgram(camera, "constant_vertex.glsl", "constant_fragment.glsl");
}

void Scene21::createShapes()
{
    DrawableModel *sun = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(sun);

    DrawableModel *mercury = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(mercury);

    DrawableModel *venus = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(venus);

    DrawableModel *earth = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(earth);

    DrawableModel *mars = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(mars);

    DrawableModel *jupiter = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(jupiter);

    DrawableModel *moon = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(0));
    shapes->push_back(moon);
}

void Scene21::createTextures()
{
    // TODO: impl if needed
}

void Scene21::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene21::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}