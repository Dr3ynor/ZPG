//
// Created by jakub on 7.10.23.
//

#ifndef TEST3_TRANSLATE_H
#define TEST3_TRANSLATE_H
#include "Transform.h"

class Translate : public Transform {
private:
    glm::vec3 translation;

public:
    Translate(glm::vec3 translation);
    glm::mat4 M;
    virtual glm::mat4 apply(glm::mat4 matrix) override;
};


#endif //TEST3_TRANSLATE_H
