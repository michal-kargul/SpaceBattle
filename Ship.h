#pragma once

#include "Entity.h"
#include <cmath>

class Ship : public Entity
{
public:
    Ship(const std::string& textureName, const float maxVelocity, const float acceleration);

protected:
    const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) override;

private:
    
};
