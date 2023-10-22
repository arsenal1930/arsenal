#pragma once
#ifndef GAMEMATH
#define GAMEMATH
#include<cmath>
#include<SFML/System/Vector2.hpp>

namespace Math { 
	template <typename T> 
	T length(const sf::Vector2<T>& vec);
	
	template <typename T> 
	T Clump(T curr, T delta, T limit);

	template <typename T> 
	sf::Vector2<T> Normalize(const sf::Vector2<T>& vec);
}

#endif
