#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Observer.h"
#include "LightManager.h"
#include "Camera.h"

class Camera;

class Shader : public Observer
{
public:
    Shader(Camera *camera, LightManager *lightManager, const char *vertexPath, const char *fragmentPath);
    ~Shader();
    void use() const;
    bool setUniformMatrix(const char *name, glm::mat4 M);
    void update(const char *viewName, const char *projectName, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection);
    void updateLights();
    void sendMatrixToShader();

    // Overloaded updateUniform methods
    bool updateUniform(const char *viewName, const char *projecName, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void updateUniform(const char *variable, const GLfloat *value);
    void updateUniform(const char *variable, glm::vec3 value);
    void updateUniform(const char *variable, float value);
    void updateUniform(const char *variable, int value);

private:
    void setVertexShader(const char *path);
    void setFragmentShader(const char *path);
    void linkShader();
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    GLuint programId;
    VertexShader *vertexShader;
    FragmentShader *fragmentShader;
    LightManager *lightManager;
    void updatePointLights();
    void updateSpotLights();
    void updateSpotLightCameraLight();
    void updateDirectionalLight();
    void logEvents();
};
