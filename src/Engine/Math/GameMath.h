#pragma once
#ifndef GAMEMATH
#define GAMEMATH
#include<cmath>
#include<SFML/Graphics.hpp>
#define V2fNULL sf::Vector2f()
#define V2iNULL sf::Vector2i()

namespace gm { 
    
    float VecModule(const sf::Vector2f& vec);
    float VecModule(const sf::Vector2i& vec);
	sf::Vector2f Normalize(const sf::Vector2f& vec);
	sf::Vector2i Normalize(const sf::Vector2i& vec);
    template<typename T> T Clump(T curr, T delta, T limit);
}

#endif
