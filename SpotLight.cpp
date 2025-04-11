#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float angle, glm::vec3 lightColor)
	: SpotLightCamera(constant, linear, quadratic, angle, lightColor)
{
	this->position = position;
	this->direction = direction;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->angle = angle;
}
