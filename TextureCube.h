#pragma once

#include "Texture.h"

class TextureCube : public Texture
{
private:
	const char *top;
	const char *bottom;
	const char *front;
	const char *back;
	const char *right;
	const char *left;

public:
	TextureCube(const char *top, const char *bottom, const char *front, const char *back, const char *right, const char *left);
	void bind(bool rgb2bgr = false);
};
