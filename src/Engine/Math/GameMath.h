#pragma once
#ifndef GAMEMATH
#define GAMEMATH
#include<cmath>
#include<SFML/Graphics.hpp>

namespace Math { 
    float VecModule(const sf::Vector2f& vec);
	sf::Vector2f Normalize(const sf::Vector2f& vec);
    template<typename T> T Clump(T curr, T delta, T limit);
}

#endif
