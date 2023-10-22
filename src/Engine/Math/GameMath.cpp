#include "GameMath.h"

float Math::VecModule(const sf::Vector2f& vec)
{
    return sqrt((vec.x*vec.x) + (vec.y*vec.y));
}

sf::Vector2f Math::Normalize(const sf::Vector2f& vec) 
{
	float len = VecModule(vec);
	return (len > 0) ? sf::Vector2f(vec.x / len, vec.y / len) : vec;
}

template<typename T> T Math::Clump(T curr, T delta, T limit) 
{
    if(delta > 0) return (curr + delta >= limit) ? limit : (curr + delta);
    if(delta < 0) return (curr + delta <= limit) ? limit : (curr + delta);
    return curr;
}
