//
// Created by jakub on 15.10.23.
//

#ifndef TEST3_OBSERVER_H
#define TEST3_OBSERVER_H

#include <glm/glm.hpp>

class Observer
{
public:
    virtual void update(const char viewName[99], const char projecName[99], glm::mat4 viewMatrix, glm::mat4 projectMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection) = 0;
    virtual void updateLights() = 0;
};

#endif // TEST3_OBSERVER_H
