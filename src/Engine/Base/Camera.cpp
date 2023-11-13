#include "../Base/Camera.h"

Camera::Camera(sf::Rect<float> rect)
{
    mainView.setViewport(rect);
}
Camera::Camera(sf::RenderWindow &window)
{
    window.getViewport(mainView);
    setOnWindow(window);
}
Camera::~Camera()
{
}

void Camera::move(sf::Vector2<float> offset)
{
    mainView.move(offset);
}

void Camera::set(sf::Vector2<float> position,sf::RenderWindow &window)
{
    mainView.setCenter(position);
    window.setView(mainView);
}

void Camera::setOnWindow(sf::RenderWindow &window)
{
    window.setView(mainView);
}