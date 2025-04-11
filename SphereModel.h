#pragma once

#include "AbstractShape.h"
#include "sphere.h"

class SphereModel : public AbstractShape
{
public:
	SphereModel();
	void draw();
};