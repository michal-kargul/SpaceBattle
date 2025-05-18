#pragma once

#include "Entity.h"
#include <cmath>

enum Directions
{
    NOT_MOVING,
    SAME_MOVING_DIRECTIONS,
    MOVING_UP,
    MOVING_DOWN,
    MOVING_RIGHT,
    MOVING_LEFT,
    HEADING_UP,
    HEADING_DOWN,
    HEADING_LEFT,
    HEADING_RIGHT,
    TILT_RIGHT,
    TILT_LEFT,
};

class Ship : public Entity
{
public:
    Ship(const std::string& textureName, const float maxVelocity, const float acceleration);

    void processShipState();
    void animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime) override;

protected:
    const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) override;
    int dx=0;
    int dy=0;
    std::unordered_map<Directions, bool> directions;

private:
    float angleDeg = 0;
};
