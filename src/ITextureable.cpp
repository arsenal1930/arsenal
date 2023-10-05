#include "ITextureable.h"

ITextureable::ITextureable()
{
    if (!texture.loadFromFile("cat.jpg"))
    {
    }
    sprite.setTexture(this->texture);
}
ITextureable::~ITextureable() {}
sf::Sprite &ITextureable::getSprite() { return this->sprite; }