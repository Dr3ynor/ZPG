//
// Created by jakub on 27.10.23.
//

#pragma once

#include <vector>
#include "Observer.h"
#include "Subject.h"

class Light : public Subject
{
private:
public:
    Light();
    Light(glm::vec3 lightColor);
    ~Light() = default;
    void addObserver(Observer *observer) override;
    void removeObserver(Observer *observer) override;
    void notify() override;

    glm::vec3 lightColor;
};