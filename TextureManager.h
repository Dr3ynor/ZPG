#pragma once

#include "Texture2D.h"
#include "TextureCube.h"

#include <vector>

class TextureManager
{
private:
	std::vector<Texture *> textures;

public:
	void addTexture(Texture *texture, bool rgb2bgr = false);
	Texture *getTexture(int i);
};
