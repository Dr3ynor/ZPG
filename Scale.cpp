//
// Created by jakub on 7.10.23.
//

#include "Scale.h"

Scale::Scale(glm::vec3 scaling)
{
    this->scaling = scaling;
}

glm::mat4 Scale::apply(glm::mat4 matrix)
{
    return glm::scale(matrix, scaling);
}