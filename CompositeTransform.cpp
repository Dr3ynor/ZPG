//
// Created by jakub on 7.10.23.
//

#include "CompositeTransform.h"

glm::mat4 CompositeTransform::apply(glm::mat4 matrix)
{
    for (const auto &transform : transforms)
    {
        matrix = transform->apply(matrix);
    }
    return matrix;
}

void CompositeTransform::addTransform(std::unique_ptr<Transform> transform)
{
    transforms.push_back(std::move(transform));
}