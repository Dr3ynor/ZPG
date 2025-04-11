#pragma once

#include "Observer.h"
#include <vector>

class Subject
{
public:
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notify() = 0;

protected:
    std::vector<Observer *> observers;
};