#pragma once

#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Math/GameMath.h"

class Object
{
private:
    class Collision
    {
    private:
        sf::Rect<float> rectCollision;
        std::vector<std::reference_wrapper<Object>> containedObjects;

    public:
        void add(float x = 0, float y = 0, float width = 0, float height = 0) // прибавляет к параметрам класса Rect в rectCollision значения из параметров функции
        {
            rectCollision.left += x;
            rectCollision.top += y;

            rectCollision.width += width;
            rectCollision.height += height;
        }
        void set(float x, float y, float width, float height) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        {
            rectCollision.left = x;
            rectCollision.top = y;

            rectCollision.width = width;
            rectCollision.height = height;
        }
        Collision &onCollisionEnter(std::vector<Object> &objects, int actionId)
        {
            for (int i = 0; i < objects.size(); i++)
                if (&objects.at(i).getCollision() != this && objects.at(i).getCollision().intersects(this->rectCollision))
                {
                    if (containedObjects.size() == 0 || [](std::vector<std::reference_wrapper<Object>> &containedObjects, std::vector<Object> &objects, int i)
                        {
                            for (int j = 0; j < containedObjects.size(); j++)
                                if (&objects.at(i).getCollision() == &(containedObjects.at(j).get().getCollision()))
                                return false;
                            return true; }(this->containedObjects, objects, i))
                    {
                        this->containedObjects.push_back(objects.at(i));
                        objects.at(i).action(actionId);
                        return objects.at(i).getCollision();
                    }
                }
        }
        Collision &onCollisionStay(std::vector<Object> &objects, int actionId)
        {
            for (int i = 0; i < objects.size(); i++)
                for (int j = 0; j < containedObjects.size(); j++)
                    if (&objects.at(i).getCollision() == &(this->containedObjects.at(j).get().getCollision()))
                    {
                        objects.at(i).action(actionId);
                        break;
                    }
        }
        Object &onCollisionExit(Object &owner, int actionId)
        {
            for (int j = 0; j < this->containedObjects.size(); j++)
                if (!(this->containedObjects.at(j).get().getCollision().intersects(this->rectCollision)))
                {
                    Object &colliderReference = (this->containedObjects.at(j).get());
                    this->containedObjects.at(j).get().action(actionId);
                    this->containedObjects.erase(this->containedObjects.begin() + j);
                    return colliderReference;
                }
        }
        bool intersects(sf::Rect<float> collider)
        {
            return this->rectCollision.intersects(collider);
        }
    };

    Collision collider;

    sf::Vector2f input;
    float speedModifier = 0.01f;

    int id;

protected:
    std::vector<int> actions{0, 1, 2, 3};

public:
    void setInput(sf::Vector2f input)
    {
        this->input = gm::Normalize(input);
    }

    Collision &getCollision() { return this->collider; }
    Object(int id, float sizeX = 100, float sizeY = 100, float x = 0, float y = 0)
    {
        this->collider.add(x, y, sizeX, sizeY);
        this->id = id;
    }
    void physicsUpdate(std::vector<Object> &objects)
    {
        this->collider.onCollisionEnter(objects, actions.at(1));
        this->collider.onCollisionStay(objects, actions.at(2));
        this->collider.onCollisionExit(*this, actions.at(3));
        this->move();
    }
    void move()
    {
        this->move(this->input * speedModifier);
        // std::cout << this->input.x << '\t' << this->input.y << std::endl;
    }
    void move(float x, float y)
    {
        this->collider.add(x, y);
    }
    void move(sf::Vector2f input)
    {
        this->collider.add(input.x, input.y);
    }
    // ввожу систему действий по кодам действия, таким образом действия с кодами 1,2,3 будут соответствовать вхождению, нахождению и выходу из коллизии соответственно
    // блять только понял какие есть с этим проблемы
    //  однако чего не сделаешь ради полиморфизма
    virtual void action(int code)
    {
        switch (code)
        {
        case 1:
            std::cout << "Enter " << this->id << std::endl;
            // std::cout << "Pobeda1 " << std::endl;
            break;
        case 2:
            std::cout << "Stay " << this->id << std::endl;
            // std::cout << "Pobeda2 " << std::endl;
            break;
        case 3:
            std::cout << "Exit " << this->id << std::endl;
            // std::cout << "Pobeda3 " << std::endl;
            break;
        }
    }
};

#endif