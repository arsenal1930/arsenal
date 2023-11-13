#include "Denizen.h"

void Denizen::setInput(sf::Vector2f input)
{
    this->input = gm::Normalize(input);
}
void Denizen::move()
{
    this->sprite.move(this->input*speedModifier);
}