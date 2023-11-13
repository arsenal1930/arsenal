#pragma once

#define EngineInit
#//define DEBUG

#include <SFML/Graphics.hpp>
#include <memory>
#include "Base/TheWorld.h"

#ifdef DEBUG
#include <iostream>
#endif

class Engine
{
private:
	sf::RenderWindow *mainWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "arsenal");
	// Игровой фон в виде прямоугольника
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(1280, 720));
	// Текстура прямоугольника
	sf::Texture background_texture;
	// Метод обработки событий
	void input();
	// Метод обновления переменных, свойств и методов, физики
	void update(sf::Time const &deltaTime, bool onAnimUpdate);
	// Метод отрисовки объектов в графическом окне
	void draw();
	// Поганит настройки окна
	void windowSettingUp();

	TheWorld *mainWorld = nullptr;

	float animationFrameRate, animationDelta;

public:
	// Конструктор
	Engine(TheWorld *world, float animationFrameRate);
	// Метод запуска игрового цикла
	void run();
};
