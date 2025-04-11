#include "Light.h"

Light::Light()
{
    this->lightColor = glm::vec3(1.0f, 1.0f, 0.0f); // default color
}

Light::Light(glm::vec3 lightColor)
{
    this->lightColor = lightColor;
}

void Light::addObserver(Observer *observer)
{
    this->observers.push_back(observer);
    notify();
}

void Light::removeObserver(Observer *observer)
{
    /*auto observerObj = std::remove(observers.begin(), observers.end(), observer);
    this->observers.erase(observerObj, observers.end());
    notify();*/
}

void Light::notify()
{
    for (int i = 0; i < observers.size(); i++)
    {
        this->observers[i]->updateLights();
    }
}
