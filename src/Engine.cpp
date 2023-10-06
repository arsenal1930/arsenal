#include "Engine.h"

void Engine::input()
{
	// Объект события
	sf::Event event_play;

	while (mainWindow->pollEvent(event_play)) // Присвоение отловленного события, объекту событий event_play
	{
		switch (event_play.type)
		{
			case sf::Event::KeyPressed:
				switch (event_play.key.code)
				{
					default:
						break;
				}
			case sf::Event::KeyReleased:
				switch (event_play.key.code)
				{
					case sf::Keyboard::A:
					case sf::Keyboard::D:
					case sf::Keyboard::W:
					case sf::Keyboard::S:
						mainWorld->getDenizen(0).setInput(sf::Vector2f(
							sf::Keyboard::isKeyPressed(sf::Keyboard::D) - 
							sf::Keyboard::isKeyPressed(sf::Keyboard::A),
							sf::Keyboard::isKeyPressed(sf::Keyboard::S) - 
							sf::Keyboard::isKeyPressed(sf::Keyboard::W)
						));
						break;
					case sf::Keyboard::Escape:
						mainWindow->close();
						break;
					default:
						break;
				}
				break;
			case sf::Event::Closed:
				mainWindow->close();
				break;
			default:
				break;
		}
		
	}
}

void Engine::update(sf::Time const &deltaTime)
{
	for (int i = 0; i < mainWorld->getDenizensSize(); i++)
	{
		mainWorld->getDenizen(i).move();
	}
}

void Engine::draw()
{
	// Очистка графического окна
	mainWindow->clear();
	// Отрисовка фона в графическом окне
	mainWindow->draw(background);
	for (int i = 0; i < mainWorld->getDenizensSize(); i++)
	{
		mainWindow->draw(mainWorld->getDenizen(i).getSprite());
	}
	// Вывод объектов в графическом окне
	mainWindow->display();
}

Engine::Engine(TheWorld *world)
{
	this->mainWorld = world;
	// Загрузка текстуры
	background_texture.loadFromFile("images/background.jpg");
	// Получение ссылки на текстуру для прямоугольника
	background.setTexture(&background_texture);
}

void Engine::run()
{
	// Объявление переменной часы
	sf::Clock clock;
	// Цикл работает пока окно открыто
	while (mainWindow->isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}
