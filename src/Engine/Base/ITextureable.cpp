#include "ITextureable.h"

ITextureable::ITextureable(std::string path) {
    if (!texture.loadFromFile(path)) {return;}
    sprite.setTexture(this->texture);
}
ITextureable::~ITextureable() {}
sf::Sprite &ITextureable::getSprite() { return this->sprite; }
