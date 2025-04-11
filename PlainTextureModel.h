#pragma once

#include "AbstractShape.h"
#include "plain_texture.h"

class PlainTextureModel : public AbstractShape
{
public:
	PlainTextureModel();
	void draw();
};
