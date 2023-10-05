#pragma once
#ifndef ITextureableInit
#define ITextureableInit

#include <SFML/Graphics.hpp>

class ITextureable
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    sf::Sprite &getSprite();

    ITextureable();
    ~ITextureable();
};
#endif