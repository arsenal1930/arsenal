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
        void add(sf::Vector2f position = V2fNULL, float width = 0, float height = 0) // прибавляет к параметрам класса Rect в rectCollision значения из параметров функции
        {
            rectCollision.left += position.x;
            rectCollision.top += position.y;

            rectCollision.width += width;
            rectCollision.height += height;
        }
        void lset(sf::Vector2f position, float width, float height, sf::Vector2f locale) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        {
            rectCollision.left = locale.x + position.x;
            rectCollision.top = locale.y + position.y;

            rectCollision.width = width;
            rectCollision.height = height;
        }
        void lset(sf::Rect<int> rect, sf::Vector2f locale) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        {
            rectCollision.left += rect.left + locale.x;
            rectCollision.top += rect.top + locale.y;

            rectCollision.width = rect.width;
            rectCollision.height = rect.height;
        }
        void gset(float x, float y, float width, float height) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        {
            rectCollision.left = x;
            rectCollision.top = y;

            rectCollision.width = width;
            rectCollision.height = height;
        }
        // вернёт объект зашедший
        Object &onCollisionEnter(std::vector<Object> &objects, int actionId)
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
                        return objects.at(i);
                    }
                }
        }
        // делает действие у объекта в списке содержащихся объектов
        void onCollisionStay(std::vector<Object> &objects, int actionId)
        {
            for (int i = 0; i < objects.size(); i++)
                for (int j = 0; j < containedObjects.size(); j++)
                    if (&objects.at(i).getCollision() == &(this->containedObjects.at(j).get().getCollision()))
                    {
                        objects.at(i).action(actionId);
                        break;
                    }
        }
        // делает действие объекта на его выходе из себя
        std::vector<std::reference_wrapper<Object>> &onCollisionExit(Object &owner, int actionId)
        {
            std::vector<std::reference_wrapper<Object>> colliderRecerences;
            for (int j = 0; j < this->containedObjects.size(); j++)
                if (!(this->containedObjects.at(j).get().getCollision().intersects(this->rectCollision)))
                {
                    Object &colliderReference = (this->containedObjects.at(j).get());
                    this->containedObjects.at(j).get().action(actionId);
                    this->containedObjects.erase(this->containedObjects.begin() + j);
                    colliderRecerences.push_back(colliderReference);
                }
            return colliderRecerences;
        }
        // проверяет пересечение своей коллизии с другой
        bool intersects(sf::Rect<float> collision)
        {
            return this->rectCollision.intersects(collision);
        }
    };

    class Animator
    { // sosilalka
        sf::Sprite sprite;
        int currentAnimation = 0;
        class Animation
        {
            bool isActive = false;

            sf::Texture tilemap;
            int currentFrame = 0, maxFrame = 0;
            class Frame
            {

                sf::Vector2i picturePosition;
                sf::Vector2i pictureSize;

                sf::Vector2i collisionPosition;
                sf::Vector2i collisionSize;

            public:
                Frame(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL)
                {

                    this->picturePosition = picturePosition;
                    this->pictureSize = pictureSize;

                    this->collisionPosition = collisionPosition;
                    this->collisionSize = collisionSize;
                }
                void add(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL)
                {

                    this->picturePosition += picturePosition;
                    this->pictureSize += pictureSize;

                    this->collisionPosition += collisionPosition;
                    this->collisionSize += collisionSize;
                }
                void gset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL)
                {

                    this->picturePosition = picturePosition;
                    this->pictureSize = pictureSize;

                    this->collisionPosition = collisionPosition;
                    this->collisionSize = collisionSize;
                }
                void lset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL,
                    sf::Vector2i collisionPositionLocale = V2iNULL)
                {

                    this->picturePosition = picturePosition;
                    this->pictureSize = pictureSize;

                    this->collisionPosition = collisionPositionLocale + collisionPosition;
                    this->collisionSize = collisionSize;
                }
                sf::Rect<int> getFramePict()
                {
                    return sf::Rect<int>(picturePosition, pictureSize);
                }
                sf::Rect<int> getFrameCollision()
                {
                    return sf::Rect<int>(collisionPosition, pictureSize);
                }
            };
            std::vector<Frame> frames;

        public:
            sf::Sprite updateFrame()
            {
                if (!this->isActive || this->currentFrame == this->maxFrame)
                {
                    this->currentFrame = 0;
                }
                else
                {
                    this->currentFrame++;
                }
                return sf::Sprite(this->tilemap, this->frames.at(currentFrame).getFramePict());
            }
            sf::Rect<int> updateCollision()
            {
                return this->frames.at(currentFrame).getFrameCollision();
            }
        };
        public:
        void updateAnimation(Collision &collision)
        {
            this->sprite = this->animations.at(this->currentAnimation).updateFrame();
            collision.lset(this->animations.at(this->currentAnimation).updateCollision(),this->sprite.getGlobalBounds().getPosition());
        }
        sf::Sprite &getSprite()
        {
            return this->sprite;
        }
        std::vector<Animation> animations;
    };
    Collision collision;
    Animator animator;
    sf::Vector2f input;
    float speedModifier = 0.01f;

    int id;

protected:
    std::vector<int> actions{0, 1, 2, 3}; // бинды действий , 1-3 на столкновения , остальные изменяются детьми

public:
    // ввод Input
    void setInput(sf::Vector2f input)
    {
        this->input = gm::Normalize(input);
    }
    // вернёт ссылку на коллизию для дальнейших взаимодействий
    Collision &getCollision() { return this->collision; }
    Object(int id, float sizeX = 100, float sizeY = 100, sf::Vector2f position = V2fNULL)
    {
        this->collision.add(position, sizeX, sizeY);
        this->id = id;
    }
    // виртуальные для возможного переопределения в детях
    virtual void physicsUpdate(std::vector<Object> &objects)
    {
        this->collision.onCollisionEnter(objects, actions.at(1));
        this->collision.onCollisionStay(objects, actions.at(2));
        this->collision.onCollisionExit(*this, actions.at(3));
        this->move(this->input * speedModifier);
        this->animator.updateAnimation(collision);
    }
    sf::Sprite & draw(){
        return this->animator.getSprite();
    }
    void move(float x, float y)
    {
        this->collision.add(sf::Vector2f(x, y));
    }
    void move(sf::Vector2f input)
    {
        this->collision.add(input);
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