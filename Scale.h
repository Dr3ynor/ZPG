//
// Created by jakub on 7.10.23.
//

#ifndef TEST3_SCALE_H
#define TEST3_SCALE_H
#include "Transform.h"

class Scale : public Transform
{
private:
    glm::vec3 scaling;

public:
    Scale(glm::vec3 scaling);

    virtual glm::mat4 apply(glm::mat4 matrix) override;
};

#endif // TEST3_SCALE_H
