#include "Transformation.h"

CompositeTransformation::~CompositeTransformation()
{
    for (auto t : transformations)
    {
        delete t;
    }
}

void CompositeTransformation::addTransformation(Transformation *t)
{
    transformations.push_back(t);
}

glm::mat4 CompositeTransformation::getMatrix4()
{
    glm::mat4 result = glm::mat4(1.0f);
    for (auto t : transformations)
    {
        result = t->getMatrix4() * result;
    }
    return result;
}

void CompositeTransformation::removeTransformation(Transformation *t)
{
    transformations.erase(std::remove(transformations.begin(), transformations.end(), t), transformations.end());
}

void CompositeTransformation::clear()
{
    for (auto t : transformations)
    {
        delete t;
    }
    transformations.clear();
}

void CompositeTransformation::pop()
{
    delete transformations.back();
    transformations.pop_back();
}

Translation::Translation(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

glm::mat4 Translation::getMatrix4()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

Rotation::Rotation(float angleRad, float x, float y, float z)
{
    this->angle = angleRad;
    this->x = x;
    this->y = y;
    this->z = z;
}

glm::mat4 Rotation::getMatrix4()
{
    return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(x, y, z));
}

Scale2::Scale2(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

glm::mat4 Scale2::getMatrix4()
{
    return glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}
