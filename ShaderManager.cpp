#include "ShaderManager.h"

ShaderManager::ShaderManager(LightManager *lightManager)
{
	this->lightManager = lightManager;
}

void ShaderManager::addShaderProgram(Camera *camera, const char *vertexShaderFile, const char *fragmentShaderFile)
{
	Shader *shader = new Shader(camera, lightManager, vertexShaderFile, fragmentShaderFile);
	shaders.push_back(shader);
	camera->addObserver(shader);
}

Shader *ShaderManager::getShaderProgram(int index)
{
	if (index < 0 || index >= shaders.size())
	{
		printf("Shader %d can not be fetched!\n", index);
	}

	return this->shaders[index];
}

void ShaderManager::updateLights()
{
	for (Shader *s : shaders)
	{
		s->use();

		s->updateLights();
	}
}
