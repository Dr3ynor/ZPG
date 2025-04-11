#include "SpotLightCamera.h"

SpotLightCamera::SpotLightCamera(float constant, float linear, float quadratic, float angle, glm::vec3 lightColor)
	: Light(lightColor)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->angle = angle;
}
