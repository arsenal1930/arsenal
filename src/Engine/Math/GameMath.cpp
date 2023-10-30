#include "GameMath.h"

template <typename T>
T gm::VecLength(const sf::Vector2<T>& vec)
{
	return std::sqrt((vec.x*vec.x) + (vec.y*vec.y));
}

template <typename T>
sf::Vector2<T> gm::Normalize(const sf::Vector2<T>& vec)
{
	float len = VecLength(vec);
	return (len > 0) ? sf::Vector2<T>(vec.x / len, vec.y / len) : vec;
}

template <typename T>
T gm::Clump(T curr, T delta, T limit)
{
	if(delta > 0) return (curr + delta >= limit) ? limit : (curr + delta);
	if(delta < 0) return (curr + delta <= limit) ? limit : (curr + delta);
	return curr;
}

template int gm::VecLength(const sf::Vector2<int>& vec);
template long gm::VecLength(const sf::Vector2<long>& vec);
template float gm::VecLength(const sf::Vector2<float>& vec);
template double gm::VecLength(const sf::Vector2<double>& vec);

template sf::Vector2<float> gm::Normalize(const sf::Vector2<float>&);
template sf::Vector2<double> gm::Normalize(const sf::Vector2<double>&);

template float gm::Clump(float, float, float);
template double gm::Clump(double, double, double);
template int gm::Clump(int, int, int);
template long gm::Clump(long, long, long);
