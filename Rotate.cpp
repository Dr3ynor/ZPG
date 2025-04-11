//
// Created by jakub on 7.10.23.
//

#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis)
{
    this->angle = angle;
    this->axis = axis;
}

glm::mat4 Rotate::apply(glm::mat4 matrix)
{
    return glm::rotate(matrix, angle, axis);
}