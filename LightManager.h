#pragma once
#include <vector>
#include <iostream>

#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "SpotLightCamera.h"
#include "DirectionalLight.h"

class LightManager
{
private:
	std::vector<PointLight *> pointLights;
	std::vector<SpotLight *> spotLights;
	SpotLightCamera *spotlightCameraLight;
	DirectionalLight *directionalLight;

public:
	PointLight *getPointLight(int i);
	SpotLight *getSpotLight(int i);
	SpotLightCamera *getSpotLightCameraLight();
	DirectionalLight *getDirectionalLight();

	void addPointLight(PointLight *pointLight);
	int getPointLightsSize();

	void addSpotLight(SpotLight *spotLight);
	int getSpotLightsSize();

	void addSpotLightCameraLight(SpotLightCamera *spotLightCameraLight);
	void addDirectionalLight(DirectionalLight *directionalLight);
};
