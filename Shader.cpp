#include "Shader.h"

Shader::Shader(Camera *camera, LightManager *lightManager, const char *vertexPath, const char *fragmentPath)
{
    programId = glCreateProgram();

    printf("Shader: program ID assigned: %u, phragment shader file: %s", programId, fragmentPath);

    this->viewMatrix = glm::mat4(1.0f);
    this->projectionMatrix = glm::mat4(1.0f);

    this->lightManager = lightManager;
    camera->addObserver(this);

    setVertexShader(vertexPath);
    setFragmentShader(fragmentPath);
    linkShader();
    update("viewMatrix", "projectionMatrix", this->viewMatrix, this->projectionMatrix, camera->cameraPosition, camera->cameraDirection);
}

Shader::~Shader()
{
    delete vertexShader;
    delete fragmentShader;

    glDeleteProgram(programId);
}

void Shader::linkShader()
{
    glLinkProgram(programId);
}

void Shader::setVertexShader(const char *path)
{
    vertexShader = new VertexShader();
    vertexShader->readShader(path);
    vertexShader->attach(programId);
}

void Shader::setFragmentShader(const char *path)
{
    fragmentShader = new FragmentShader();
    fragmentShader->readShader(path);
    fragmentShader->attach(programId);
}

void Shader::use() const
{
    glUseProgram(programId);
}

bool Shader::setUniformMatrix(const char *name, glm::mat4 M)
{
    GLint location = glGetUniformLocation(programId, name);
    if (location == -1)
    {
        return false;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &M[0][0]);

    return true;
}

void Shader::sendMatrixToShader()
{
    GLint viewMatrixUniformLocation = glGetUniformLocation(programId, "viewMatrix");
    glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->viewMatrix));

    GLint projectionMatrixUniformLocation = glGetUniformLocation(programId, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
}

void Shader::update(const char *viewName, const char *projectName, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection)
{
    updateUniform(viewName, projectName, viewMatrix, projectionMatrix);

    updateUniform("cameraPosition", cameraPosition);
    updateUniform("cameraDirection", cameraDirection);
    updateLights();
}

bool Shader::updateUniform(const char *viewName, const char *projecName, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    this->projectionMatrix = projectionMatrix;
    this->viewMatrix = viewMatrix;

    return true;
}

void Shader::updateUniform(const char *variable, const GLfloat *value)
{
    GLint location = glGetUniformLocation(programId, variable);

    if (location == -1)
    {
        // printf("[Program ID: %u] OpenGL: Error updateUniform(const char *variable, const GLfloat *value), variable: %s, value: %f\n", programId, variable, value);
    }

    GLenum errorEnum = glGetError();
    if (errorEnum != GL_NO_ERROR)
    {
        printf("OpenGL: Error errorEnum: %u\n\n", errorEnum);
    }

    logEvents();

    if (location >= 0)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }
}

void Shader::updateUniform(const char *variable, glm::vec3 value)
{
    GLint location = glGetUniformLocation(programId, variable);

    if (location == -1)
    {
        // printf("[Program ID: %u] OpenGL: Error updateUniform(const char *variable, glm::vec3 value), variable: %s, value: [%f %f %f]\n", programId, variable, value.x, value.y, value.z);
    }

    GLenum errorEnum = glGetError();
    if (errorEnum != GL_NO_ERROR)
    {
        printf("OpenGL: Error errorEnum: %u\n\n", errorEnum);
    }

    logEvents();

    if (location >= 0)
    {
        glUniform3f(location, value.x, value.y, value.z);
    }
}

void Shader::updateUniform(const char *variable, float value)
{
    GLint location = glGetUniformLocation(programId, variable);

    if (location == -1)
    {
        // printf("[Program ID: %u] OpenGL: Error updateUniform(const char *variable, float value), variable: %s, value: %f\n", programId, variable, value);
    }

    GLenum errorEnum = glGetError();
    if (errorEnum != GL_NO_ERROR)
    {
        printf("OpenGL: Error errorEnum: %u\n\n", errorEnum);
    }

    logEvents();

    if (location >= 0)
    {
        glUniform1f(location, value);
    }
}

void Shader::updateUniform(const char *variable, int value)
{
    GLint location = glGetUniformLocation(programId, variable);

    if (location == -1)
    {
        // printf("[Program ID: %u] OpenGL: Error updateUniform(const char *variable, int value), variable: %s, value: %d\n", programId, variable, value);
    }

    GLenum errorEnum = glGetError();
    if (errorEnum != GL_NO_ERROR)
    {
        printf("OpenGL: Error errorEnum: %u\n\n", errorEnum);
    }

    logEvents();

    if (location >= 0)
    {
        glUniform1i(location, value);
    }
}

void Shader::logEvents()
{
    GLint infoLogLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength + 1);
    glGetProgramInfoLog(programId, infoLogLength, NULL, &infoLog[0]);
    std::string str(infoLog.begin(), infoLog.end());

    if (str.empty())
        return;

    if (std::strlen(str.c_str()) == 0)
        return;

    printf("OpenGL Log event:\n%s\n", str.c_str());
}

void Shader::updatePointLights()
{
    use();

    int size = lightManager->getPointLightsSize();
    updateUniform("numberOfPointLights", size);

    for (size_t i = 0; i < size; i++)
    {
        updateUniform(("pointLights[" + std::to_string(i) + "].lightColor").c_str(), lightManager->getPointLight(i)->lightColor);
        updateUniform(("pointLights[" + std::to_string(i) + "].position").c_str(), lightManager->getPointLight(i)->position);
        updateUniform(("pointLights[" + std::to_string(i) + "].constant").c_str(), lightManager->getPointLight(i)->constant);
        updateUniform(("pointLights[" + std::to_string(i) + "].linear").c_str(), lightManager->getPointLight(i)->linear);
        updateUniform(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), lightManager->getPointLight(i)->quadratic);
    }
}

void Shader::updateSpotLights()
{
    use();

    int size = lightManager->getSpotLightsSize();
    updateUniform("numberOfSpotLights", size);

    for (size_t i = 0; i < size; i++)
    {
        updateUniform(("spotLights[" + std::to_string(i) + "].position").c_str(), lightManager->getSpotLight(i)->position);
        updateUniform(("spotLights[" + std::to_string(i) + "].direction").c_str(), lightManager->getSpotLight(i)->direction);
        updateUniform(("spotLights[" + std::to_string(i) + "].lightColor").c_str(), lightManager->getSpotLight(i)->lightColor);
        updateUniform(("spotLights[" + std::to_string(i) + "].constant").c_str(), lightManager->getSpotLight(i)->constant);
        updateUniform(("spotLights[" + std::to_string(i) + "].linear").c_str(), lightManager->getSpotLight(i)->linear);
        updateUniform(("spotLights[" + std::to_string(i) + "].quadratic").c_str(), lightManager->getSpotLight(i)->quadratic);
        updateUniform(("spotLights[" + std::to_string(i) + "].angle").c_str(), lightManager->getSpotLight(i)->angle);
    }
}

void Shader::updateSpotLightCameraLight()
{
    use();

    if (lightManager->getSpotLightCameraLight() != NULL)
    {
        updateUniform("spotLightCamera_bool", true);
        updateUniform("spotLightCameraLight.lightColor", lightManager->getSpotLightCameraLight()->lightColor);
        updateUniform("spotLightCameraLight.constant", lightManager->getSpotLightCameraLight()->constant);
        updateUniform("spotLightCameraLight.linear", lightManager->getSpotLightCameraLight()->linear);
        updateUniform("spotLightCameraLight.quadratic", lightManager->getSpotLightCameraLight()->quadratic);
        updateUniform("spotLightCameraLight.angle", lightManager->getSpotLightCameraLight()->angle);
    }
}

void Shader::updateDirectionalLight()
{
    use();

    if (lightManager->getDirectionalLight() != NULL)
    {
        updateUniform("directionalLight_bool", true);
        updateUniform("directional.lightColor", lightManager->getDirectionalLight()->lightColor);
        updateUniform("directional.direction", lightManager->getDirectionalLight()->direction);
    }
}

void Shader::updateLights()
{
    updatePointLights();
    updateSpotLights();
    updateSpotLightCameraLight();
    updateDirectionalLight();
}
