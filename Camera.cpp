#include "Camera.h"

Camera::Camera()
{
	width = 800;
	height = 600;

	projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	this->gravityOn = false;

	this->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);

	this->cameraDirection = cameraTarget;
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget)
{
	width = 800;
	height = 600;

	projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);

	this->gravityOn = true;

	this->cameraPosition = glm::vec3(cameraPosition.x, this->gravityOn ? 1 : cameraPosition.y, cameraPosition.z);
	this->cameraTarget = cameraTarget;

	this->cameraDirection = cameraTarget;
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::addObserver(Observer *observer)
{
	this->observers.push_back(observer);

	notify();
}

void Camera::removeObserver(Observer *observer)
{
	// auto observerObj = std::remove(observers.begin(), observers.end(), observer);
	// this->observers.erase(observerObj, observers.end());
	// notify();
}

void Camera::notify()
{
	viewMatrix = glm::lookAt(cameraPosition, cameraTarget + cameraPosition, cameraUp);
	projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);

	for (auto &observer : observers)
	{
        printf("CAMERAPOS: %f %f %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
		observer->update("viewMatrix", "projectionMatrix", viewMatrix, projectionMatrix, cameraPosition, cameraDirection);
	}
}

void Camera::changeCamera(int key)
{
	float cameraSpeed = 1.0f;
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	switch (key)
	{
		// W
	case 87:
		cameraPosition += cameraSpeed * glm::vec3(cameraTarget.x, this->gravityOn ? 1 : cameraTarget.y, cameraTarget.z);
		break;
		// S
	case 83:
		cameraPosition -= cameraSpeed * glm::vec3(cameraTarget.x, this->gravityOn ? 1 : cameraTarget.y, cameraTarget.z);
		break;
		// D
	case 68:
		cameraPosition += glm::normalize(glm::cross(glm::vec3(cameraTarget.x, this->gravityOn ? 1 : cameraTarget.y, cameraTarget.z), cameraUp)) * cameraSpeed;
		break;
		// A
	case 65:
		cameraPosition -= glm::normalize(glm::cross(glm::vec3(cameraTarget.x, this->gravityOn ? 1 : cameraTarget.y, cameraTarget.z), cameraUp)) * cameraSpeed;
		break;
	}

	// Propagate change of gravity flag to view
	cameraPosition = glm::vec3(cameraPosition.x, this->gravityOn ? 1 : cameraPosition.y, cameraPosition.z);

	notify();
}

void Camera::cursorCallback(float xOffset, float yOffset)
{
	float sensitivity = 0.5f;
	xOffset = xOffset * sensitivity;
	yOffset = yOffset * sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89)
	{
		pitch = 89;
	}
	if (pitch < -89)
	{
		pitch = -89;
	}
	if (yaw > 360)
	{
		yaw = yaw - 360;
	}
	if (yaw < 0)
	{
		yaw = yaw + 360;
	}

	cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection.y = sin(glm::radians(pitch));
	cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraTarget = glm::normalize(cameraDirection);

	notify();
}

void Camera::setWidthAndHeight(int width, int height)
{
	this->width = width;
	this->height = height;
}

glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}
