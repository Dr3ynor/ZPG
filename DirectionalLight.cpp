#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 lightColor)
	: Light(lightColor)
{
	this->direction = direction;
}
