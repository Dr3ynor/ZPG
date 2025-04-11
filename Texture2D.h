#pragma once

#include "Texture.h"

class Texture2D : public Texture
{
private:
	const char *filePath;

public:
	Texture2D(const char *filePath);
	void bind(bool rgb2bgr = false);
};
