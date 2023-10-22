#include "Denizen.h"

void Denizen::setInput(sf::Vector2<float> input)
{
    this->input = Math::Normalize<float>(input);
}
void Denizen::move()
{
    this->sprite.move(this->input*speedModifier);
}
