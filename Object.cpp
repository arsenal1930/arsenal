#include "Object.h"

void Object::Collision::add(sf::Vector2f position, float width, float height) // прибавляет к параметрам класса Rect в rectCollision значения из параметров функции
{
    rectCollision.left += position.x;
    rectCollision.top += position.y;

    rectCollision.width += width;
    rectCollision.height += height;
}
void Object::Collision::lset(sf::Vector2f position, float width, float height, sf::Vector2f locale) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
{
    rectCollision.left = locale.x + position.x;
    rectCollision.top = locale.y + position.y;

    rectCollision.width = width;
    rectCollision.height = height;
}
void Object::Collision::lset(sf::Rect<int> rect, sf::Vector2f locale) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
{
    rectCollision.left = rect.left + locale.x;
    rectCollision.top = rect.top + locale.y;

    rectCollision.width = rect.width;
    rectCollision.height = rect.height;
}
void Object::Collision::gset(float x, float y, float width, float height) // то же, что и .add, но вместо прибавления задаёт параметры класса Rect в Collider.
{
    rectCollision.left = x;
    rectCollision.top = y;

    rectCollision.width = width;
    rectCollision.height = height;
}
// вернёт объект зашедший
Object &Object::Collision::onCollisionEnter(std::vector<Object> &objects, int actionId)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (&objects.at(i).getCollision() != this && objects.at(i).getCollision().intersects(rectCollision))
        {
            if (containedObjects.size() == 0 || [](std::vector<std::reference_wrapper<Object>> &containedObjects, std::vector<Object> &objects, int i)
                {
                            for (int j = 0; j < containedObjects.size(); j++)
                                if (&objects.at(i).getCollision() == &(containedObjects.at(j).get().getCollision()))
                                return false;
                            return true; }(containedObjects, objects, i))
            {
                containedObjects.push_back(objects.at(i));
                objects.at(i).action(actionId);
                return objects.at(i);
            }
        }
    }
}
// делает действие у объекта в списке содержащихся объектов
void Object::Collision::onCollisionStay(std::vector<Object> &objects, int actionId)
{
    for (int i = 0; i < objects.size(); i++)
        for (int j = 0; j < containedObjects.size(); j++)
            if (&objects.at(i).getCollision() == &(containedObjects.at(j).get().getCollision()))
            {
                objects.at(i).action(actionId);
                break;
            }
}
// делает действие объекта на его выходе из себя
std::vector<std::reference_wrapper<Object>> &Object::Collision::onCollisionExit(Object &owner, int actionId)
{
    std::vector<std::reference_wrapper<Object>> colliderRecerences;
    for (int j = 0; j < containedObjects.size(); j++)
        if (!(containedObjects.at(j).get().getCollision().intersects(rectCollision)))
        {
            Object &colliderReference = (containedObjects.at(j).get());
            containedObjects.at(j).get().action(actionId);
            containedObjects.erase(containedObjects.begin() + j);
            colliderRecerences.push_back(colliderReference);
        }
    return colliderRecerences;
}
// проверяет пересечение своей коллизии с другой
bool Object::Collision::intersects(sf::Rect<float> collision)
{
    return rectCollision.intersects(collision);
}

Object::Animator::Animation::Frame::Frame(
    sf::Vector2i picturePosition,
    sf::Vector2i pictureSize,
    sf::Vector2i collisionPosition,
    sf::Vector2i collisionSize)
{

    this->picturePosition = picturePosition;
    this->pictureSize = pictureSize;

    this->collisionPosition = collisionPosition;
    this->collisionSize = collisionSize;
}
void Object::Animator::Animation::Frame::add(
    sf::Vector2i picturePosition,
    sf::Vector2i pictureSize,
    sf::Vector2i collisionPosition,
    sf::Vector2i collisionSize)
{

    this->picturePosition += picturePosition;
    this->pictureSize += pictureSize;

    this->collisionPosition += collisionPosition;
    this->collisionSize += collisionSize;
}
void Object::Animator::Animation::Frame::gset(
    sf::Vector2i picturePosition,
    sf::Vector2i pictureSize,
    sf::Vector2i collisionPosition,
    sf::Vector2i collisionSize)
{

    this->picturePosition = picturePosition;
    this->pictureSize = pictureSize;

    this->collisionPosition = collisionPosition;
    this->collisionSize = collisionSize;
}
void Object::Animator::Animation::Frame::lset(
    sf::Vector2i picturePosition,
    sf::Vector2i pictureSize,
    sf::Vector2i collisionPosition,
    sf::Vector2i collisionSize,
    sf::Vector2i collisionPositionLocale)
{

    this->picturePosition = picturePosition;
    this->pictureSize = pictureSize;

    this->collisionPosition = collisionPositionLocale + collisionPosition;
    this->collisionSize = collisionSize;
}
sf::Rect<int> Object::Animator::Animation::Frame::getFramePict()
{
    return sf::Rect<int>(picturePosition, pictureSize);
}
sf::Rect<int> Object::Animator::Animation::Frame::getFrameCollision()
{
    return sf::Rect<int>(collisionPosition, pictureSize);
}

void Object::Animator::Animation::enable()
{
    isActive = true;
}
void Object::Animator::Animation::disable()
{
    isActive = false;
}
void Object::Animator::Animation::setTileset(std::string adress)
{
    if (!tilemap.loadFromFile(adress))
    {
    }
}
void Object::Animator::Animation::addFrame(
    sf::Vector2i picturePosition,
    sf::Vector2i pictureSize,
    sf::Vector2i collisionPosition,
    sf::Vector2i collisionSize)
{
    frames.push_back(Frame(picturePosition, pictureSize, collisionPosition, collisionSize));
}
sf::Rect<int> Object::Animator::Animation::updateFrame()
{
    //std::cout << "oy" << '\n';
    if (!isActive || currentFrame == maxFrame - 1)
    {
        currentFrame = 0;
    }
    else
    {
        currentFrame++;
    }
    //std::cout << "og " << currentFrame << ' ' << frames.size() << '\n';
    return frames.at(currentFrame).getFramePict();
}
sf::Rect<int> Object::Animator::Animation::updateCollision()
{
    return frames.at(currentFrame).getFrameCollision();
}

Object::Animator::Animator(std::string adressTxt)
{
    readAnimator(adressTxt);
    setAnimation(currentAnimation);
}
void Object::Animator::updateAnimation(Collision &collision)
{
    //std::cout << "oo" << '\n';
    sf::Vector2f position = sprite.getPosition();
    //std::cout << "oi " << currentAnimation << '\n';
    sprite.setTextureRect(animations.at(currentAnimation).updateFrame());
    //std::cout << "ol" << '\n';
    sprite.setPosition(position);
    //std::cout << "op" << '\n';
    collision.lset(animations.at(currentAnimation).updateCollision(), sprite.getPosition());
    //std::cout << "ok" << '\n';
}
void Object::Animator::setAnimation(int number)
{
    animations.at(currentAnimation).disable();
    currentAnimation = number;
    animations.at(currentAnimation).enable();
}
sf::Sprite &Object::Animator::getSprite()
{
    return sprite;
}
void Object::Animator::moveSprite(float x, float y)
{
    sprite.move(x, y);
}
void Object::Animator::readAnimator(std::string adress)
{
    std::string line;
    std::ifstream myfile;
    myfile.open(adress);
    if (myfile)
    {
        while (getline(myfile, line))
        {
            switch (line[0])
            {
            case 'N':
            {
                Animation newAnimation;
                int k = 0;
                std::string newLine = "";
                for (int i = 1; i < line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        newLine += line[i];
                    }
                    else
                    {
                        k++;
                        switch (k)
                        {
                        case 1:
                        {
                            newAnimation.name = newLine;
                        }
                        break;
                        case 2:
                        {
                            newAnimation.setTileset(newLine);
                        }
                        break;
                        case 3:
                        {
                            newAnimation.maxFrame = stoi(newLine);
                        }
                        break;
                        }
                        newLine = "";
                    }
                }
                animations.push_back(newAnimation);
            }
            break;
            case 'F':
            {
                int pictPosX, pictPosY, pictSizeX, pictSizeY, colliderLocPosX, colliderLocPosY, colliderSizeX, colliderSizeY;
                int k = 0;
                std::string newLine = "";
                for (int i = 1; i < line.length(); i++)
                {
                    if (line[i] != ' ')
                        newLine += line[i];
                    else
                    {
                        k++;
                        switch (k)
                        {
                        case 2:
                        {
                            pictPosX = stoi(newLine);
                        }
                        break;
                        case 3:
                        {
                            pictPosY = stoi(newLine);
                        }
                        break;
                        case 4:
                        {
                            pictSizeX = stoi(newLine);
                        }
                        break;
                        case 5:
                        {
                            pictSizeY = stoi(newLine);
                        }
                        break;
                        case 6:
                        {
                            colliderLocPosX = stoi(newLine);
                        }
                        break;
                        case 7:
                        {
                            colliderLocPosY = stoi(newLine);
                        }
                        break;
                        case 8:
                        {
                            colliderSizeX = stoi(newLine);
                        }
                        break;
                        case 9:
                        {
                            colliderSizeY = stoi(newLine);
                        }
                        break;
                        }
                        newLine = "";
                    }
                }
                animations.at(animations.size() - 1).addFrame(sf::Vector2i(pictPosX, pictPosY), sf::Vector2i(pictSizeX, pictSizeY), sf::Vector2i(colliderLocPosX, colliderLocPosY), sf::Vector2i(colliderSizeX, colliderSizeY));
            }
            break;
            }
        }
    }
    myfile.close();
}
// ввод Input
void Object::setInput(sf::Vector2f input)
{
    this->input = gm::Normalize(input);
}

sf::Sprite &Object::draw()
{
    return animator->getSprite();
}

void Object::move(float x, float y)
{
    animator->moveSprite(x, y);
}

void Object::move(sf::Vector2f input)
{
    animator->moveSprite(input.x, input.y);
}
void Object::action(int code)
{
    switch (code)
    {
    case 1:
        //std::cout << "Enter " << id << std::endl;
        break;
    case 2:
        // //std::cout << "Stay " << id << std::endl;
        break;
    case 3:
        //std::cout << "Exit " << id << std::endl;
        break;
    }
}
Object::Object(int id, float sizeX, float sizeY, sf::Vector2f position, std::string adressTxt)
{
    animator = new Animator(adressTxt);
    collision.add(position, sizeX, sizeY);
    this->id = id;
    std::cout << id << '\t' << std::endl;
}
// виртуальные для возможного переопределения в детях
void Object::physicsUpdate(std::vector<Object> &objects)
{
    //std::cout << id << '\t' << objects.size() << '\n';
    collision.onCollisionEnter(objects, actions.at(1));
    //std::cout << id << '\t' << objects.size() << '\n';
    collision.onCollisionStay(objects, actions.at(2));
    //std::cout << id << '\t' << objects.size() << '\n';
    collision.onCollisionExit(*this, actions.at(3));
    //std::cout << id << '\t' << objects.size() << '\n';
    move(input * speedModifier);
    //std::cout << id << '\t' << objects.size() << '\n';
    animator->updateAnimation(collision);
    //std::cout << id << '\t' << objects.size() << '\n';
}
Object::~Object()
{
    delete animator;
}
// вернёт ссылку на коллизию для дальнейших взаимодействий
Object::Collision &Object::getCollision() { return collision; }