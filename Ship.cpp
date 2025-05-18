#include "Ship.h"

Ship::Ship(const std::string& textureName, const float maxVelocity, const float acceleration)
    : Entity(textureName, maxVelocity, acceleration)
{
    
}

const float Ship::calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative)
{
    float dx = sf::Mouse::getPosition(relative).x - currPos.x;
    float dy = sf::Mouse::getPosition(relative).y - currPos.y;

    float angleRad = std::atan2(dy, dx);
    float angleDeg = (angleRad * 180.f / 3.14159265f) + 90;

    if (angleDeg < 0.f)
        angleDeg += 360.f;

    return angleDeg;
}