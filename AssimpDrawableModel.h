#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "AbstractShape.h"

class AssimpDrawableModel : public AbstractShape
{
protected:
	int count;

public:
	AssimpDrawableModel(char *filePath);
	void draw();
};
