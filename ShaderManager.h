#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <stdio.h>

#include "Shader.h"
#include "LightManager.h"
#include "TextureManager.h"

class ShaderManager
{
private:
	std::vector<Shader *> shaders;
	LightManager *lightManager;

public:
	ShaderManager(LightManager *lightManager);
	void addShaderProgram(Camera *camera, const char *vertexShaderFile, const char *fragmentShaderFile);
	Shader *getShaderProgram(int index);
	void updateLights();
};