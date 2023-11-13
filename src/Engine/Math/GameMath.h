#pragma once
#ifndef GAMEMATH
#define GAMEMATH
#include<cmath>
#include <functional>
#include<SFML/System/Vector2.hpp>
#define V2fNULL sf::Vector2f()
#define V2iNULL sf::Vector2i()

namespace gm 
{ 
	template <typename T> 
	T VecLength(const sf::Vector2<T>& vec);
	
	template <typename T> 
	T Clump(T curr, T delta, T limit);

	template <typename T> 
	sf::Vector2<T> Normalize(const sf::Vector2<T>& vec);
}

#endif //GAMEMATH
