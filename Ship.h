#pragma once

#include "Entity.h"
#include <cmath>

class Ship : public Entity
{
public:
    Ship(const std::string& textureName, const float maxVelocity, const float acceleration);

    void animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime) override;

protected:
    const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) override;
    int dx=0;
    int dy=0;

private:
    float angleDeg = 0;
};
