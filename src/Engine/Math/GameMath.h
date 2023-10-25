#pragma once
#ifndef GAMEMATH
#define GAMEMATH
#include<cmath>
#include<SFML/Graphics.hpp>
#define Vector2fNULL sf::Vector2f()

namespace gm { 
    
    float VecModule(const sf::Vector2f& vec);
	sf::Vector2f Normalize(const sf::Vector2f& vec);
    template<typename T> T Clump(T curr, T delta, T limit);
}

#endif
