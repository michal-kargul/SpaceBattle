#pragma once

#include "Entity.h"

class Ship : public Entity {
public:
    Ship(const std::string& textureName);

    void update(sf::Time deltaTime);       // logika np. ruchu/animacji
    void handleInput(const sf::Keyboard::Key key, bool isPressed);

private:
    float speed = 200.f;                   // jednostki na sekundê
    sf::Vector2f velocity;

    std::size_t currentFrame = 0;          // do animacji
    sf::Time animationTime;
    sf::Time timePerFrame = sf::seconds(0.1f);
};
