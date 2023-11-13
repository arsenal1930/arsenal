#pragma once

#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "../Math/GameMath.h"

// #define DEBUGPHYSICS

class Object
{
private:
    class Collision
    {
    private:
        sf::Rect<float> rectCollision;

        std::vector<std::reference_wrapper<Object>> containedObjects;
        bool isInContainedObjects(std::vector<std::reference_wrapper<Object>> &, Object &, size_t);

    public:
        void add(sf::Vector2f position = V2fNULL, float width = 0, float height = 0);     // прибавляет к параметрам класса Rect в rectCollision значения из параметров функции
        void lset(sf::Vector2f position, float width, float height, sf::Vector2f locale); // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        void lset(sf::Rect<int> rect, sf::Vector2f locale);                               // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
        void gset(float x, float y, float width, float height);                           // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.

        // вернёт объект зашедший
        Object &onCollisionEnter(std::vector<Object> &objects, int actionId);
        // делает действие у объекта в списке содержащихся объектов
        void onCollisionStay(std::vector<Object> &objects, int actionId);
        // делает действие объекта на его выходе из себя
        std::vector<std::reference_wrapper<Object>> &onCollisionExit(Object &owner, int actionId);
        // проверяет пересечение своей коллизии с другой
        bool intersects(sf::Rect<float> collision);
    };

    class Animator
    {
        sf::Sprite sprite;
        int currentAnimation = 0;
        class Animation
        {
            sf::Texture tilemap;
            bool isActive = false;
            int currentFrame = 0;
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
                    sf::Vector2i collisionSize = V2iNULL);
                void add(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL);
                void gset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL);
                void lset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL,
                    sf::Vector2i collisionPositionLocale = V2iNULL);
                sf::Rect<int> getFramePict();
                sf::Rect<int> getFrameCollision();
            };
            std::vector<Frame> frames{};

        public:
            int maxFrame = 0;
            std::string name;
            void enable();
            void disable();
            void setTileset(std::string adress);
            sf::Texture &getTileset();
            Animation() {}
            void addFrame(
                sf::Vector2i picturePosition = V2iNULL,
                sf::Vector2i pictureSize = V2iNULL,
                sf::Vector2i collisionPosition = V2iNULL,
                sf::Vector2i collisionSize = V2iNULL);
            sf::Rect<int> updateFrame();
            sf::Rect<int> updateCollision();
        };
        std::vector<Animation> animations;

    public:
        std::string adressTxt;
#ifdef DEBUG
        std::string debugString;
#endif // DEBUG
        Animator() {}
        Animator(std::string adressTxt);
        void initialize(std::string adressTxt);
        void updateAnimation(Collision &collision);
        void setAnimation(int number, sf::Sprite &sprite);
        sf::Sprite &getSprite();
        void moveSprite(float x, float y);
        void readAnimator(std::string adress);
    };
    Collision collision;
    Animator animator;
    sf::Vector2f input;
    float speedModifier = 70.0f;

    int id;

protected:
    std::vector<int> actions{0, 1, 2, 3}; // бинды действий , 1-3 на столкновения , остальные изменяются детьми

public:
    // ввод Input
    void setInput(sf::Vector2f input);
    // вернёт ссылку на коллизию для дальнейших взаимодействий
    Collision &getCollision();
    Object(int id, float sizeX = 100, float sizeY = 100, sf::Vector2f position = V2fNULL, std::string adressTxt = "texts/example.txt");
    Object(int id, float speedModifier, float sizeX = 100, float sizeY = 100, sf::Vector2f position = V2fNULL, std::string adressTxt = "texts/example.txt");
    virtual ~Object();
    // виртуальные для возможного переопределения в детях
    virtual void physicsUpdate(std::vector<Object> &objects, float delta);
    virtual void animationUpdate();
    virtual void update();
    sf::Sprite &draw();
    void move(float x, float y);
    void move(sf::Vector2f input);
    virtual void action(int code);
};

using vecObjRefs = std::vector<std::reference_wrapper<Object>>;
#endif