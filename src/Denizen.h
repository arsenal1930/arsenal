#pragma once
#ifndef DenizenInit
#define DenizenInit

#include "IAnimable.h"
#include "GameMath.h"

class Denizen : public IAnimable
{
private:
    sf::Vector2f input;
    float speedModifier = 1.0f;

public:
    Denizen()
    {
    }
    void setInput(sf::Vector2f input);
    void move();
};

#endif
