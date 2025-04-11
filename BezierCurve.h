#pragma once

#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

class BezierCurve
{
private:
	float parameter = 0.12f;
	float delta = 0.009f;

	glm::mat4 bezierCubic = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
									  glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
									  glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
									  glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	glm::mat4x3 matrix;
	glm::vec4 parameters;

	void setParameters();

public:
	BezierCurve(glm::mat4x3 matrix);
	glm::vec3 getPoint();
};
