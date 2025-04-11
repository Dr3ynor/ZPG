#include "LightManager.h"

void LightManager::addPointLight(PointLight *pointLight)
{
	this->pointLights.push_back(pointLight);
}

int LightManager::getPointLightsSize()
{
    return this->pointLights.size();
}

void LightManager::addSpotLight(SpotLight *spotLight)
{
	this->spotLights.push_back(spotLight);
}

int LightManager::getSpotLightsSize()
{
    return this->spotLights.size();
}

void LightManager::addSpotLightCameraLight(SpotLightCamera *spotLightCameraLight)
{
	this->spotlightCameraLight = spotLightCameraLight;
}

void LightManager::addDirectionalLight(DirectionalLight *directionalLight)
{
	this->directionalLight = directionalLight;
}

PointLight *LightManager::getPointLight(int i)
{
	return this->pointLights[i];
}

SpotLight *LightManager::getSpotLight(int i)
{
	return this->spotLights[i];
}

SpotLightCamera *LightManager::getSpotLightCameraLight()
{
	return this->spotlightCameraLight;
}

DirectionalLight *LightManager::getDirectionalLight()
{
	return this->directionalLight;
}
