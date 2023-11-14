#include "Directions.h"

direction fromVec2dir(const sf::Vector2f &vec)
{
        int dir = std::floor(0.5 * std::ceil(std::atan2(vec.x, vec.y) / (M_PI_4))) + 1;
        dir = (dir == -1) ? 3 : dir;
        return static_cast<direction>(dir);
}
