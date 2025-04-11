//
// Created by jakub on 7.10.23.
//

#ifndef TEST3_TRANSFORM_H
#define TEST3_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "memory"

class Transform
{
public:
    virtual glm::mat4 apply(glm::mat4 matrix) = 0;
    virtual ~Transform() = default;
    virtual void addTransform(std::unique_ptr<Transform> transform) {}
};

#endif // TEST3_TRANSFORM_H
