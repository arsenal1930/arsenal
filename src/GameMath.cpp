#include "GameMath.h"

sf::Vector2f Math::Normalize(const sf::Vector2f& vec) {
	float len = sqrt((vec.x*vec.x) + (vec.y*vec.y));
	return len ? sf::Vector2f(vec.x / len, vec.y / len) : vec;
}
