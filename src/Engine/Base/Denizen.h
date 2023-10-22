#pragma once
#ifndef DenizenInit
#define DenizenInit

#include "IAnimable.h"
#include "../Math/GameMath.h"

class Denizen : public IAnimable
{
private:
    sf::Vector2<float> input;
    float speedModifier = 0.1f;

public:
    Denizen()
    {
    }
    void setInput(sf::Vector2<float> input);
    void move();
};

#endif
