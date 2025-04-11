
#pragma once

#include <vector>
#include "Light.h"

class PointLight : public Light
{
private:
public:
    PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
    ~PointLight() = default;

    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
};