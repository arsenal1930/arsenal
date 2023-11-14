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

bool Object::Collision::isInContainedObjects(vecObjRefs &containedObjects, Object &object, size_t i)
{
    for (size_t j = 0; j < containedObjects.size(); j++)
        if (&(object.getCollision()) == &(containedObjects.at(j).get().getCollision()))
            return false;
    return true;
}

// вернёт объект зашедший
Object &Object::Collision::onCollisionEnter(std::vector<Object> &objects, int actionId)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (&objects.at(i).getCollision() != this && objects.at(i).getCollision().intersects(rectCollision))
        {
            if (containedObjects.size() == 0 || isInContainedObjects(containedObjects, objects.at(i), i))
            {
                containedObjects.push_back(objects.at(i));
                objects.at(i).action(actionId);
                return objects.at(i);
            }
        }
    }
    return objects.at(0);
    // TODO objects.at(0) должен содержать пустой объект
}
// делает действие у объекта в списке содержащихся объектов
void Object::Collision::onCollisionStay(std::vector<Object> &objects, int actionId)
{
    for (size_t i = 0; i < objects.size(); i++)
        if (isInContainedObjects(containedObjects, objects.at(i), i))
            objects.at(i).action(actionId);
}
// делает действие объекта на его выходе из себя
vecObjRefs &Object::Collision::onCollisionExit(Object &owner, int actionId)
{
    static vecObjRefs colliderRecerences;
    for (size_t j = 0; j < containedObjects.size(); j++)
        if (!(containedObjects.at(j).get().getCollision().intersects(rectCollision)))
        {
            containedObjects.at(j).get().action(actionId);
            colliderRecerences.push_back(containedObjects.at(j).get());
            containedObjects.erase(containedObjects.begin() + j);
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
void Object::Animator::Animation::setTileset(std::string address)
{
    if (!tilemap.loadFromFile(address))
        ;
}
sf::Texture &Object::Animator::Animation::getTileset()
{
    return tilemap;
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
    if (!isActive || currentFrame == maxFrame - 1)
    {
        currentFrame = 0;
    }
    else
    {
        currentFrame++;
    }
#ifdef DEBUGANIM
    std::cout << currentFrame << maxFrame << ' ' << isActive << ' ' << '\n'
              << "left: " << frames.at(currentFrame).getFramePict().left << "\ntop: " << frames.at(currentFrame).getFramePict().top << "\nwidth " << frames.at(currentFrame).getFramePict().width << "\nheight: " << frames.at(currentFrame).getFramePict().height << '\n';
#endif // DEBUGANIM
    return frames.at(currentFrame).getFramePict();
}
sf::Rect<int> Object::Animator::Animation::updateCollision()
{
    return frames.at(currentFrame).getFrameCollision();
}

Object::Animator::Animator(std::string adressTxt)
{
    readAnimator(adressTxt);
    setAnimation(currentAnimation, sprite);
}
void Object::Animator::initialize(std::string adressTxt)
{
    readAnimator(adressTxt);
    setAnimation(currentAnimation, sprite);
}
void Object::Animator::updateAnimation(Collision &collision)
{

#ifdef DEBUGANIM
    std::cout << currentAnimation << " Updating in Animator " << &sprite << '\n'
              << "left: " << sprite.getTextureRect().left << '\n'
              << "top: " << sprite.getTextureRect().top << '\n'
              << "width: " << sprite.getTextureRect().width << "\nheight: " << sprite.getTextureRect().height << '\n';

#endif // DEBUGANIM
    sf::Vector2f position = sprite.getPosition();
    sprite.setTextureRect(animations.at(currentAnimation).updateFrame());
    sprite.setPosition(position);
    collision.lset(animations.at(currentAnimation).updateCollision(), sprite.getPosition());
}
void Object::Animator::setAnimation(int number, sf::Sprite &sprite)
{
    animations.at(currentAnimation).disable();
    currentAnimation = number;
    sprite.setTexture(animations.at(currentAnimation).getTileset());
    animations.at(currentAnimation).enable();
}
void Object::Animator::setAnimation(sf::Sprite &sprite, std::string name)
{
    animations.at(currentAnimation).disable();
    for (size_t i = 0; i < animations.size(); i++)
        if (animations.at(i).name == name)
            currentAnimation = i;
    sprite.setTexture(animations.at(currentAnimation).getTileset());
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
void Object::Animator::readAnimator(std::string address)
{
    Animation newAnimation;
    int pictPosX, pictPosY,
        pictSizeX, pictSizeY,
        colliderLocPosX, colliderLocPosY,
        colliderSizeX, colliderSizeY;

    addressTxt = address;
    std::string line, word, path;
    std::ifstream myfile;
    myfile.open(address);
    if (myfile)
    {
        while (myfile >> word)
        {
            switch (word[0])
            {
            case 'N':
                myfile >> newAnimation.name >> path >> newAnimation.maxFrame;
                newAnimation.setTileset(path);
                animations.push_back(newAnimation);
                break;
            case 'F':
                myfile >> pictPosX >> pictPosY >> pictSizeX >> pictSizeY >> colliderLocPosX >> colliderLocPosY >> colliderSizeX >> colliderSizeY;
                animations.at(animations.size() - 1).addFrame(sf::Vector2i(pictPosX, pictPosY), sf::Vector2i(pictSizeX, pictSizeY), sf::Vector2i(colliderLocPosX, colliderLocPosY), sf::Vector2i(colliderSizeX, colliderSizeY));
                break;
            }
        }
    }
    myfile.close();
}
// ввод Input
// this->dir - direction of movement
void Object::setInput(sf::Vector2f input)
{
    this->input = gm::Normalize(input); // член
}

void Object::setDirection(sf::Vector2f input)
{
    if (input == V2fNULL) return;
    this->dir = fromVec2dir(input);
}

sf::Sprite &Object::draw()
{
    return animator.getSprite();
}

void Object::move(float x, float y)
{
    animator.moveSprite(x, y);
}

void Object::move(sf::Vector2f input)
{
    animator.moveSprite(input.x, input.y);
}
sf::Vector2<float> Object::getSpritePosition()
{
    // ПЕРЕДЕЛАТЬ
    return animator.getSprite().getGlobalBounds().getPosition() + animator.getSprite().getGlobalBounds().getSize() / 2.0f;
}
void Object::action(int code)
{
    switch (code)
    {
    case 1:
        std::cout << "Enter " << id << std::endl;
        break;
    case 2:
        // std::cout << "Stay " << id << std::endl;
        break;
    case 3:
        std::cout << "Exit " << id << std::endl;
        break;
    }
}
Object::Object(int id, float sizeX, float sizeY, sf::Vector2f position, std::string adressTxt)
{
    animator.initialize(adressTxt);
    collision.add(position, sizeX, sizeY);
    this->id = id;
}
Object::Object(int id, float speedModifier, float sizeX, float sizeY, sf::Vector2f position, std::string adressTxt)
{
    animator.initialize(adressTxt);
    collision.add(position, sizeX, sizeY);
    this->id = id;
    this->speedModifier = speedModifier;
}
void Object::animationUpdate()
{
#ifdef DEBUGANIM
    std::cout << "Updating in Object " << id << '\n';
#endif // DEBUGANIM
    animator.setAnimation(dir, animator.getSprite());
    animator.updateAnimation(collision);
}
// виртуальные для возможного переопределения в детях
void Object::physicsUpdate(std::vector<Object> &objects, float delta)
{
    collision.onCollisionEnter(objects, actions.at(1));
    collision.onCollisionStay(objects, actions.at(2));
    collision.onCollisionExit(*this, actions.at(3));
    move(input * speedModifier * delta);
#ifdef DEBUGPHYSICS
    std::cout << delta << '\n';
#endif // DEBUGPHYSICS
}
void Object::update() {}
Object::~Object()
{
}
// вернёт ссылку на коллизию для дальнейших взаимодействий
Object::Collision &Object::getCollision() { return collision; }