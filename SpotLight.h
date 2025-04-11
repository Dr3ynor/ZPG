#pragma once

#include "SpotLightCamera.h"

class SpotLight : public SpotLightCamera
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	SpotLight(glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float angle, glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
};
