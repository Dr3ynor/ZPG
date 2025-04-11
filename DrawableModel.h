#pragma once

#include "Transformation.h"
#include "Shader.h"
#include "AbstractShape.h"
#include "Texture.h"

#include <utility>
#include <vector>
#include <iostream>

class DrawableModel
{
public:
    DrawableModel(AbstractShape *shape, Shader *shaderProgram);
    ~DrawableModel();
    void draw();
    void drawSkybox();
    void addTransformation(Transformation *transformation);
    void clearTransformations();
    void popTransformation();
    void addTexture(Texture *texture);
    void updateTexture(const char *uniformVariable, int index);
    std::vector<Texture *> textures;
    bool isVisible = true;

private:
    CompositeTransformation *compositeTransformation;
    Shader *shaderProgram;
    AbstractShape *shape;
};
