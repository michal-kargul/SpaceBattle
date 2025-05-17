#include "Ship.h"

Ship::Ship(const std::string& textureName)
    : Entity(textureName), velocity(0.f, 0.f), animationTime(sf::Time::Zero)
{
    // dodatkowa inicjalizacja, jeœli potrzebna
}

void Ship::update(sf::Time deltaTime)
{
    //// animacja
    //animationTime += deltaTime;

    //if (animationTime >= timePerFrame) {
    //    animationTime = sf::microseconds(animationTime.asMicroseconds() % timePerFrame.asMicroseconds());
    //    currentFrame = (currentFrame + 1) % getTextureCount(); // zak³adamy, ¿e masz tak¹ metodê
    //    setFrame(currentFrame); // zak³adamy, ¿e masz tak¹ metodê
    //}

    //// ruch
    //move(velocity * deltaTime.asSeconds()); // zak³adamy, ¿e Entity ma metodê move()
}
