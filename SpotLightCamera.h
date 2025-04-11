#pragma once

#include "Light.h"

class SpotLightCamera : public Light
{
public:
	float constant;
	float linear;
	float quadratic;
	float angle;

	SpotLightCamera(float constant, float linear, float quadratic, float angle, glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
};
