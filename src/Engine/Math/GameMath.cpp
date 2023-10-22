#include "GameMath.h"

	
template <typename T>
T Math::length(const sf::Vector2<T>& vec)
{
	return std::sqrt((vec.x*vec.x) + (vec.y*vec.y));
}

template <typename T>
sf::Vector2<T> Math::Normalize(const sf::Vector2<T>& vec)
{
	T len = length(vec);
	return (len > 0) ? vec / len : vec;
}

template <typename T>
T Math::Clump(T curr, T delta, T limit)
{
	if(delta > 0) return (curr + delta >= limit) ? limit : (curr + delta);
	if(delta < 0) return (curr + delta <= limit) ? limit : (curr + delta);
	return curr;
}


template float Math::length(const sf::Vector2<float>& vec);
template double Math::length(const sf::Vector2<double>& vec);
template long double Math::length(const sf::Vector2<long double>& vec);

template sf::Vector2<float> Math::Normalize(const sf::Vector2<float>&);
template sf::Vector2<double> Math::Normalize(const sf::Vector2<double>&);
template sf::Vector2<long double> Math::Normalize(const sf::Vector2<long double>&);
