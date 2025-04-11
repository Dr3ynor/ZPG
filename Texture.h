#pragma once

#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <opencv4/opencv2/opencv.hpp>
using namespace cv;

class Texture
{
protected:
	GLuint textureId;

public:
	int position;
	virtual void bind(bool rgb2bgr = false) = 0;
};
