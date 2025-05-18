#pragma once

#include "Entity.h"
#include <cmath>

class Ship : public Entity
{
public:
    Ship(const std::string& textureName, const float maxVelocity, const float acceleration);

    virtual void animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime) override;
    const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) override;

protected:
    int dx=0;
    int dy=0;

private:
    
};
