#pragma once

#include "Entity.h"

class Particle : public Entity {
public:
    Particle(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const sf::Sprite& relativeSprite, const float offsetX, const float offsetY);
    Particle(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const float curVelocityX, const float curVelocityY, sf::Vector2f position);

    const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) override;

    void rotate(const float angle = 0) override;
    void move() override;

private:
    const sf::Sprite* relativeSprite = nullptr;
    float offsetX = 0;
    float offsetY = 0;
};
