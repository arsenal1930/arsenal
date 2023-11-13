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
	sf::RenderWindow *mainWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "Abrakadabra");
	// Игровой фон в виде прямоугольника
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(1280, 720));
	// Текстура прямоугольника
	sf::Texture background_texture;
	// Метод обработки событий
	void input();
	// Метод обновления переменных, свойств и методов, физики
	void update(sf::Time const &deltaTime);
	// Метод отрисовки объектов в графическом окне
	void draw();

	TheWorld *mainWorld = nullptr;

public:
	// Конструктор
	Engine(TheWorld *world);
	~Engine();
	// Метод запуска игрового цикла
	void run();
};
