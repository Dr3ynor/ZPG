//
// Created by jakub on 7.10.23.
//

#include "Translate.h"

Translate::Translate(glm::vec3 translation) {
    this->translation = translation;
}
glm::mat4 Translate::apply(glm::mat4 matrix)
{
    return glm::translate(matrix, translation);
}
