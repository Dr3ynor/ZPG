#pragma once

#include "AbstractShape.h"
#include "crossHair.h"

class CrossHairModel : public AbstractShape
{
public:
	CrossHairModel();
	void draw();
};
