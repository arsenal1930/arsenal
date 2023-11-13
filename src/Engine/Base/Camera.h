#pragma once
#ifndef CAMERA
#define CAMERA

#include <SFML/Graphics.hpp> 
#include <iostream>

class Camera
{
private:
    sf::View mainView;

public:
    Camera(sf::Rect<float> rect);
    Camera(sf::RenderWindow & window);
    ~Camera();

    void move(sf::Vector2<float> offset);
    void set(sf::Vector2<float> position,sf::RenderWindow &window);
    void setOnWindow(sf::RenderWindow & window);
};
#endif