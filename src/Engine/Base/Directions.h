#pragma once
#ifndef DIRECTIONS
#define DIRECTOINS

#include <cmath>
#include <SFML/System/Vector2.hpp>

#include <iostream>

typedef enum direct4
{
        left = 0,
        down = 1,
        right = 2,
        up = 3
} direction;

direction fromVec2dir(const sf::Vector2f &vec);

#endif