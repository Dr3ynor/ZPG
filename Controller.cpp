//
// Created by jakub on 8.10.23.
//

#include "Controller.h"

void Controller::updateRotation()
{
    this->rotationAngle = 0.01f;
}

Controller::Controller()
{
    this->rotationAngle = 0.0f;
}
