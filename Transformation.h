#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp> // original #include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <algorithm>

class Transformation
{
public:
    virtual glm::mat4 getMatrix4() = 0;
    virtual ~Transformation() = default;
};

class CompositeTransformation : public Transformation
{
public:
    ~CompositeTransformation() override;
    void addTransformation(Transformation *t);
    void removeTransformation(Transformation *t);
    void clear();
    void pop();
    glm::mat4 getMatrix4() override;

private:
    std::vector<Transformation *> transformations;
};

class Translation : public Transformation
{
public:
    Translation(float x, float y, float z);
    glm::mat4 getMatrix4() override;

private:
    float x, y, z;
};

class Rotation : public Transformation
{
public:
    Rotation(float angle, float x, float y, float z);
    glm::mat4 getMatrix4() override;

private:
    float angle, x, y, z;
};

class Scale2 : public Transformation
{
public:
    Scale2(float x, float y, float z);
    glm::mat4 getMatrix4() override;

private:
    float x, y, z;
};
