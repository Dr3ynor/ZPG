#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	glm::vec3 direction;

	DirectionalLight(glm::vec3 direction, glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
};
