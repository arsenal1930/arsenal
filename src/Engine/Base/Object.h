#pragma once

#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "../Math/GameMath.h"

// #define DEBUGPHYSICS

// Класс объекта , Отец всех , может иметь анимацию, коллизию, взаимодействие , управление игроком или ИИ
class Object
{
private:
    // Класс коллизии объекта, отвечает за коллизию объекта
    class Collision
    {
    private:
        // Коллизия объекта
        sf::Rect<float> rectCollision;
        // Список хранящихся внутри или пересекающихся с коллизией объектов
        std::vector<std::reference_wrapper<Object>> containedObjects;
        // Проверяет себя на предмет содержание в других объектах, заносит их в списочек
        bool isInContainedObjects(std::vector<std::reference_wrapper<Object>> &, Object &, size_t);

    public:
        // ПРИБАВЛЯЕТ к сущействующим характеристикам коллизии характеристики
        void add(sf::Vector2f position = V2fNULL, float width = 0, float height = 0);
        // УСТАНАВЛИВАЕТ ЛОКАЛЬНО, относительно какой-либо позиции, характеристики коллизии
        void lset(sf::Vector2f position, float width, float height, sf::Vector2f locale);
        // УСТАНАВЛИВАЕТ ЛОКАЛЬНО, относительно какой-либо позиции, характеристики коллизии
        void lset(sf::Rect<int> rect, sf::Vector2f locale);
        // УСТАНАВЛИВАЕТ ГЛОБАЛЬНО характеристики коллизии
        void gset(float x, float y, float width, float height);
        // вернёт объект зашедший
        Object &onCollisionEnter(std::vector<Object> &objects, int actionId);
        // делает действие у объекта в списке содержащихся объектов
        void onCollisionStay(std::vector<Object> &objects, int actionId);
        // делает действие объекта на его выходе из себя
        std::vector<std::reference_wrapper<Object>> &onCollisionExit(Object &owner, int actionId);
        // проверяет пересечение своей коллизии с другой
        bool intersects(sf::Rect<float> collision);
    };
    // Класс аниматора , меняет кадры и предоставляет спрайт с актуальным кадром
    class Animator
    {
        // Спрайт объекта
        sf::Sprite sprite;
        // Номер текущей анимации
        int currentAnimation = 0;
        // Класс анимации, единицы содержащей в себе кадры и их характеристики , необходимые для отображения анимации
        class Animation
        {
            // Тайлсет анимации, картинки в формате .png или .jpg, на которой изображены все кадры анимации
            sf::Texture tilemap;
            // Активен ли кадр, влияет на то, будут ли меняться кадры у этой анимации
            bool isActive = false;
            // Номер текущего кадра
            int currentFrame = 0;
            class Frame
            {
                // Позиция кадра на тайлсете
                sf::Vector2i picturePosition;
                // Размер кадра на тайлсете
                sf::Vector2i pictureSize;

                // Позиция коллизии кадра относительно спрайта/картинки
                sf::Vector2i collisionPosition;
                // Размер коллизии кадра
                sf::Vector2i collisionSize;

            public:
                // Конструктор УСТАНАВЛИВАЮЩИЙ характеристики кадра
                Frame(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL);
                // ПРИБАВЛЯЕТ к сущействующим характеристикам кадра характеристики
                void add(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL);
                // УСТАНАВЛИВАЕТ ГЛОБАЛЬНО характеристики кадра
                void gset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL);
                // УСТАНАВЛИВАЕТ ЛОКАЛЬНО, относительно какой-либо позиции, характеристики кадра
                void lset(
                    sf::Vector2i picturePosition = V2iNULL,
                    sf::Vector2i pictureSize = V2iNULL,
                    sf::Vector2i collisionPosition = V2iNULL,
                    sf::Vector2i collisionSize = V2iNULL,
                    sf::Vector2i collisionPositionLocale = V2iNULL);
                sf::Rect<int> getFramePict();
                sf::Rect<int> getFrameCollision();
            };
            // Кадры
            std::vector<Frame> frames{};

        public:
            // Количество кадров - 1
            int maxFrame = 0;
            // Имя анимации
            std::string name;
            // Включает анимацию, позволяя ей менять кадры
            void enable();
            // Выключает анимацию, непозволяя ей менять кадры
            void disable();
            // Задаёт тайлсет анимации
            void setTileset(std::string adress);
            // Возвращает изображение тайлсета
            sf::Texture &getTileset();
            // Пустой конструктор
            Animation() {}
            // Добавляет кадр в массив кадров
            void addFrame(
                sf::Vector2i picturePosition = V2iNULL,
                sf::Vector2i pictureSize = V2iNULL,
                sf::Vector2i collisionPosition = V2iNULL,
                sf::Vector2i collisionSize = V2iNULL);
            // Возвращает характеристики кадра на тайлсете для последующей установки кадра
            sf::Rect<int> updateFrame();
            // Возвращает коллизию соответствующую текущему кадру
            sf::Rect<int> updateCollision();
        };
        // Массив анимаций
        std::vector<Animation> animations;

    public:
        // Путь к текстовому файлику, в котором указаны все характеристики анимаций объекта
        std::string adressTxt;
#ifdef DEBUG
        std::string debugString;
#endif // DEBUG
       // Пустой конструктор
        Animator() {}
        // Конструктор с задачей пути к текстовому файлику с характеристиками анимаций
        Animator(std::string adressTxt);
        // Загрузка всех анимаций и задача им характеристик
        void initialize(std::string adressTxt);
        // Меняет кадр на следующий и обновляет коллизию объекта в соответствии с кадром
        void updateAnimation(Collision &collision);
        // Меняет анимацию
        void setAnimation(int number, sf::Sprite &sprite);
        // Возвращает спрайт объекта, в основном используется для отрисовки , хочу сделать дружественным , а функцию отрисовки сделать дружественной
        sf::Sprite &getSprite();
        // Двигает спрайт в пространстве
        void moveSprite(float x, float y);
        // Достаёт из файла значения аниматора
        void readAnimator(std::string adress);
    };
    // Коллизия объекта, осуществляет взаимодействие с объектами
    Collision collision;
    // Аниматор объекта, осуществляет анимацию
    Animator animator;
    // Ввод, указывает на направление движения объекта
    sf::Vector2f input;
    // Скорость объекта
    float speedModifier = 70.0f;
    // Уникальный индентификатор объекта
    int id;

protected:
    // Функция выполнения действий объекта
    std::vector<int> actions{0, 1, 2, 3}; // бинды действий , 1-3 на столкновения , остальные изменяются детьми

public:
    // Задаст направление движения объекта
    void setInput(sf::Vector2f input);
    // Вернёт ссылку на коллизию объекта для дальнейших взаимодействий
    Collision &getCollision();
    // Конструктор объекта, обязателен только индентификатор
    Object(int id, float sizeX = 100, float sizeY = 100, sf::Vector2f position = V2fNULL, std::string adressTxt = "texts/example.txt");
    // Конструктор объекта, обязателен только индентификатор
    Object(int id, float speedModifier, float sizeX = 100, float sizeY = 100, sf::Vector2f position = V2fNULL, std::string adressTxt = "texts/example.txt");
    virtual ~Object();
    // Обновляет физику объекта, осуществляет движение объекта, его взаимодействия с другими объектами
    virtual void physicsUpdate(std::vector<Object> &objects, float delta);
    // Обновляет кадр, меняет его и задаёт коллизию объекта
    virtual void animationUpdate();
    // Планируется сделать обновление физики и анимации в одной функции
    virtual void update();
    // Вернёт ссылку на спрайт текущего объекта, для отрисовки
    sf::Sprite &draw();
    // Двигает объект в пространстве
    void move(float x, float y);
    // Двигает объект в пространстве
    void move(sf::Vector2f input);
    // Производит действие из списка действий объекта, заранее указаны
    virtual void action(int code);
    // Вернёт центр спрайта, для фиксации на нём камеры
    sf::Vector2<float> getSpritePosition();
};
// Сокращает написание длииинного типа переменной, хранящей ссылки на объекты, и тут я понял, что целесообразнее хранить указатели
using vecObjRefs = std::vector<std::reference_wrapper<Object>>;

#endif