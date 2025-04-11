//
// Created by jakub on 7.10.23.
//

#ifndef TEST3_ROTATE_H
#define TEST3_ROTATE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"
class Rotate : public Transform
{
private:
    float angle;
    glm::vec3 axis;

public:
    Rotate(float angle, glm::vec3 axis);

    virtual glm::mat4 apply(glm::mat4 matrix) override;
};

#endif // TEST3_ROTATE_H
