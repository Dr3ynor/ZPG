#include "TextureManager.h"

void TextureManager::addTexture(Texture *texture, bool rgb2bgr)
{
	texture->position = this->textures.size();

	this->textures.push_back(texture);

	texture->bind(rgb2bgr);
}

Texture *TextureManager::getTexture(int i)
{
	if (i < 0 || i >= textures.size())
	{
		printf("OpenGL/OpenCV Error: Texture %d does not exist\n", i);
	}

	return this->textures[i];
}
