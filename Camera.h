#pragma once

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Subject.h"

class Shader;

class Camera : public Subject
{
public:
	Camera();
	Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	void changeCamera(int key);
	void cursorCallback(float xOffset, float yOffset);
	void setWidthAndHeight(int width, int height);
	void addObserver(Observer *observer) override;
	void removeObserver(Observer *observer) override;
	void notify() override;
	glm::vec3 cameraDirection;
	glm::vec3 cameraPosition;
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	bool gravityOn;

private:
	float width;
	float height;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
	float yaw = 0;
	float pitch = 0;
};
