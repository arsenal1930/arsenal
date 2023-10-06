#pragma once
#ifndef DenizenInit
#define DenizenInit

#include "IAnimable.h"
#include "GameMath.h"

class Denizen : public IAnimable
{
private:
    sf::Vector2f input;
    float speedModifier = 0.1f;

public:
    Denizen()
    {
    }
    void setInput(sf::Vector2f input);
    void move();
};

#endif
