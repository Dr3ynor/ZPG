#include "DrawableModel.h"

DrawableModel::DrawableModel(AbstractShape *shape, Shader *shaderProgram)
{
    this->shape = shape;
    this->shaderProgram = shaderProgram;
    this->compositeTransformation = new CompositeTransformation();
}

DrawableModel::~DrawableModel()
{
    delete compositeTransformation;
}

void DrawableModel::draw()
{
    if (shaderProgram == nullptr)
    {
        printf("draw: No shader program set for object!");
        return;
    }

    shaderProgram->use();

    int check = shaderProgram->setUniformMatrix("modelMatrix", compositeTransformation->getMatrix4());

    if (check == -1)
    {
        printf("draw: Error setting uniform modelTransform!");
        return;
    }

    shaderProgram->sendMatrixToShader();
    shape->draw();
}

void DrawableModel::drawSkybox()
{
    if (shaderProgram == nullptr)
    {
        printf("drawSkybox: No shader program set for object!");
        return;
    }

    shaderProgram->use();

    int check = shaderProgram->setUniformMatrix("modelMatrix", compositeTransformation->getMatrix4());
    if (check == -1)
    {
        printf("drawSkybox: Error setting uniform modelTransform!");
        return;
    }

    shaderProgram->sendMatrixToShader();
    shape->draw();
}

void DrawableModel::addTransformation(Transformation *transformation)
{
    compositeTransformation->addTransformation(transformation);
}

void DrawableModel::clearTransformations()
{
    compositeTransformation->clear();
}

void DrawableModel::popTransformation()
{
    compositeTransformation->pop();
}

void DrawableModel::addTexture(Texture *texture)
{
    textures.push_back(texture);
}

void DrawableModel::updateTexture(const char *textureUniformVariable, int textureIndex)
{
    shaderProgram->use();
    shaderProgram->updateUniform(textureUniformVariable, textureIndex);
}