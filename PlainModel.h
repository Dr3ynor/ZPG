#pragma once

#include "AbstractShape.h"
#include "plain.h"

class PlainModel : public AbstractShape
{
public:
	PlainModel();
	void draw();
};
