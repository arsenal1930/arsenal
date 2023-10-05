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
			case sf::Keyboard::A:
				mainWorld->getDenizen(0).addInput(-1.0f, 0.0f);
				break;
			case sf::Keyboard::D:
				mainWorld->getDenizen(0).addInput(1.0f, 0.0f);
				break;
			case sf::Keyboard::W:
				mainWorld->getDenizen(0).addInput(0.0f, -1.0f);
				break;
			case sf::Keyboard::S:
				mainWorld->getDenizen(0).addInput(0.0f, 1.0f);
				break;
			/*case sf::Keyboard::Escape:
				mainWindow->close();
				break;*/

			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event_play.key.code)
			{
			case sf::Keyboard::A:
				mainWorld->getDenizen(0).addInput(1.0f, 0.0f);
				break;
			case sf::Keyboard::D:
				mainWorld->getDenizen(0).addInput(-1.0f, 0.0f);
				break;
			case sf::Keyboard::W:
				mainWorld->getDenizen(0).addInput(0.0f, 1.0f);
				break;
			case sf::Keyboard::S:
				mainWorld->getDenizen(0).addInput(0.0f, -1.0f);
				break;
			case sf::Keyboard::Escape:
				mainWindow->close();
				break;

			default:
				break;
			}
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
	background_texture.loadFromFile("image/background.jpg");
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
