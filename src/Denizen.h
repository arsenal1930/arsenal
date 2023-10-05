#pragma once
#ifndef DenizenInit
#define DenizenInit

#include "IAnimable.h"

class Denizen : public IAnimable
{
private:
    float InputX = 0.0f;
    float InputY = 0.0f;
    float currentSpeed = 1.0f;

public:
    Denizen()
    {
    }
    void addInput(float InputX, float InputY);
    void move();
};

#endif
