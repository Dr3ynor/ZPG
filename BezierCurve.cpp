#include "BezierCurve.h"

BezierCurve::BezierCurve(glm::mat4x3 matrix)
{
	this->matrix = matrix;
}

void BezierCurve::setParameters()
{
	if (this->parameter >= 1.0f || this->parameter <= 0.0f)
	{
		this->delta *= -1;
	}

	this->parameter += this->delta;
	this->parameters = glm::vec4(this->parameter * this->parameter * this->parameter, this->parameter * this->parameter, this->parameter, 1.0f);
}

glm::vec3 BezierCurve::getPoint()
{
	setParameters();

	return parameters * bezierCubic * glm::transpose(matrix);
}
