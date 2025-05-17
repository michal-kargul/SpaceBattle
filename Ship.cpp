#include "Ship.h"

Ship::Ship(const std::string& textureName)
    : Entity(textureName), velocity(0.f, 0.f), animationTime(sf::Time::Zero)
{
    // dodatkowa inicjalizacja, je�li potrzebna
}

void Ship::update(sf::Time deltaTime)
{
    //// animacja
    //animationTime += deltaTime;

    //if (animationTime >= timePerFrame) {
    //    animationTime = sf::microseconds(animationTime.asMicroseconds() % timePerFrame.asMicroseconds());
    //    currentFrame = (currentFrame + 1) % getTextureCount(); // zak�adamy, �e masz tak� metod�
    //    setFrame(currentFrame); // zak�adamy, �e masz tak� metod�
    //}

    //// ruch
    //move(velocity * deltaTime.asSeconds()); // zak�adamy, �e Entity ma metod� move()
}
