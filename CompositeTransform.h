//
// Created by jakub on 7.10.23.
//

#ifndef TEST3_COMPOSITETRANSFORM_H
#define TEST3_COMPOSITETRANSFORM_H
#include "Transform.h"
#include <vector>
#include <memory>

class CompositeTransform : public Transform
{
private:
    std::vector<std::unique_ptr<Transform> > transforms;

public:
    void addTransform(std::unique_ptr<Transform> transform) override;
    virtual glm::mat4 apply(glm::mat4 matrix) override;
};

#endif // TEST3_COMPOSITETRANSFORM_H
