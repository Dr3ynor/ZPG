//
// Created by jakub on 29.10.23.
//

#include "Scene2.h"
#include "CompositeTransform.h"
#include "iostream"
#include "DrawableModel.h"
#include "vector"
#include "memory"

Scene2::Scene2()
    : SceneBase(
          new Camera(glm::vec3(-42.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
{
    createShaders();
    createTextures();
    createShapes();
}

glm::vec3 getCircleTrajectory(float r, float alpha)
{
    float x = r * sin(alpha);
    float z = r * cos(alpha);

    return glm::vec3(x, 0, z);
}

void Scene2::draw()
{
    // Sun
    shapes->at(0)->addTransformation(new Scale2(3.0f, 3.0f, 3.0f));

    // Mercury
    float mercuryRotationAngle = 0.1f;
    glm::vec3 mercuryTrajectory = getCircleTrajectory(6.0f, mercuryRotationAngle * rotationAngle + 0.3f);
    shapes->at(1)->addTransformation(new Scale2(0.6f, 0.6f, 0.6f));
    shapes->at(1)->addTransformation(new Translation(mercuryTrajectory.x, mercuryTrajectory.y, mercuryTrajectory.z));

    // Venus
    float venusRotationAngle = 0.15f;
    glm::vec3 venusTrajectory = getCircleTrajectory(10.0f, venusRotationAngle * rotationAngle + 0.6f);
    shapes->at(2)->addTransformation(new Translation(venusTrajectory.x, venusTrajectory.y, venusTrajectory.z));

    // Earth
    float earthRotationAngle = 0.2f;
    glm::vec3 earthTrajectory = getCircleTrajectory(13.0f, earthRotationAngle * rotationAngle + 1.1f);
    shapes->at(3)->addTransformation(new Translation(earthTrajectory.x, earthTrajectory.y, earthTrajectory.z));

    // Mars
    float marsRotationAngle = 0.22f;
    glm::vec3 marsTrajectory = getCircleTrajectory(16.0f, marsRotationAngle * rotationAngle + 2.6f);
    shapes->at(4)->addTransformation(new Scale2(0.9f, 0.9f, 0.9f));
    shapes->at(4)->addTransformation(new Translation(marsTrajectory.x, marsTrajectory.y, marsTrajectory.z));

    // Jupiter
    float jupiterRotationAngle = 0.08f;
    glm::vec3 jupiterTrajectory = getCircleTrajectory(20.0f, jupiterRotationAngle * rotationAngle + 3.8f);
    shapes->at(5)->addTransformation(new Scale2(2.0f, 2.0f, 2.0f));
    shapes->at(5)->addTransformation(new Translation(jupiterTrajectory.x, jupiterTrajectory.y, jupiterTrajectory.z));

    // Moon
    float moonOrbitRadius = 2.0f;   // Adjust the moon's orbit radius as needed
    float moonRotationAngle = 1.1f; // Choose a suitable rotation speed for the moon
    glm::vec3 moonTrajectory = getCircleTrajectory(moonOrbitRadius, moonRotationAngle * rotationAngle + 1.1f);
    // Position the moon relative to the Earth
    glm::vec3 moonPosition = earthTrajectory + moonTrajectory;
    shapes->at(6)->addTransformation(new Scale2(0.5f, 0.5f, 0.5f));
    shapes->at(6)->addTransformation(new Translation(moonPosition.x, moonPosition.y, moonPosition.z));

    for (int i = 0; i < shapes->size(); i++)
    {
        shapes->at(i)->draw();
    }

    shapes->at(0)->clearTransformations();
    shapes->at(1)->clearTransformations();
    shapes->at(2)->clearTransformations();
    shapes->at(3)->clearTransformations();
    shapes->at(4)->clearTransformations();
    shapes->at(5)->clearTransformations();
    shapes->at(6)->clearTransformations();

    rotationAngle += 0.05f;
}

void Scene2::createShaders()
{

    shaderManager->addShaderProgram(camera, "phong_vertex.glsl", "phong_fragment_multilight.glsl");
    shaderManager->addShaderProgram(camera, "constant_vertex.glsl", "constant_fragment.glsl");

    // Shader *shaderProgram = new Shader(camera, lightManager, "phong_vertex.glsl", "phong_fragment_multilight.glsl"); // Phong
    // shaders->push_back(shaderProgram);

    // Shader *shaderProgram2 = new Shader(camera, lightManager, "constant_vertex.glsl", "constant_fragment.glsl");
    // shaders->push_back(shaderProgram2);
}

void Scene2::createShapes()
{
    DrawableModel *sun = new DrawableModel(new SphereModel(), shaderManager->getShaderProgram(1));
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

void Scene2::createTextures()
{
    // TODO: impl if needed
}

void Scene2::addObjOnClick(glm::vec3 objPosition, glm::vec4 viewPort)
{
    // TODO: impl if needed
}

void Scene2::removeObjOnClick(int stencilId)
{
    // TODO: impl if needed
}