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
				mainWorld->getObject(playerId).setInput(sf::Vector2f(
					sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
						sf::Keyboard::isKeyPressed(sf::Keyboard::A),
					sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
						sf::Keyboard::isKeyPressed(sf::Keyboard::W)));
				break;
			case sf::Keyboard::Escape:
				mainWindow->close();
				break;
			case sf::Keyboard::Num0:
				camera->setOnWindow(*mainWindow);
				playerId = 0;
				break;
			case sf::Keyboard::Num1:
				camera->setOnWindow(*mainWindow);
				playerId = 1;
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

void Engine::windowSettingUp()
{
	mainWindow->setFramerateLimit(60);
	mainWindow->setMouseCursorVisible(0);
	mainWindow->setPosition(sf::Vector2<int>(0, 0));
}

void Engine::update(sf::Time const &deltaTime, bool onAnimUpdate)
{
	camera->set(mainWorld->getObject(playerId).getSpritePosition(), *mainWindow);
	for (int i = 0; i < mainWorld->getObjectsSize(); i++)
	{
		mainWorld->getObject(i).physicsUpdate(mainWorld->getList(), 0.01f); // deltaTime.asSeconds());

		if (onAnimUpdate)
		{
			mainWorld->getObject(i).animationUpdate();
		}
	}
}

void Engine::draw()
{
	// Очистка графического окна
	mainWindow->clear();
	// Отрисовка фона в графическом окне
	mainWindow->draw(background);
	for (int i = 0; i < mainWorld->getObjectsSize(); i++)
	{
		mainWindow->draw(mainWorld->getObject(i).draw());
	}
	// Вывод объектов в графическом окне
	mainWindow->display();
}

Engine::Engine(TheWorld *world, float animationFrameRate)
{
	this->mainWorld = world;
	// Загрузка текстуры
	background_texture.loadFromFile("images/background.jpg");
	// Получение ссылки на текстуру для прямоугольника
	background.setTexture(&background_texture);

	camera = new Camera(*mainWindow);

	camera->set(world->getObject(playerId).getSpritePosition(), *mainWindow);

	this->animationFrameRate = animationFrameRate;
	animationDelta = 1.0f / animationFrameRate;
}

void Engine::run()
{
	windowSettingUp();
	// Объявление переменной часы для физики
	sf::Clock clockPhysics;
	// Объявление переменной часы для анимации
	sf::Clock clockAnimation;
	// Цикл работает пока окно открыто
	while (mainWindow->isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clockPhysics.restart();

		input();
		update(dt, [&]()
			   {if(clockAnimation.getElapsedTime().asSeconds() >= animationDelta)
			{
				clockAnimation.restart();
				return 1;
			}
			else return 0; }());
		draw();
	}
}
