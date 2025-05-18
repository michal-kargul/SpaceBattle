#include "Player.h"

Player::Player(const std::string& textureName, const float maxVelocity, const float acceleration)
    : Ship(textureName, maxVelocity, acceleration)
{
}

const bool Player::handleMovementInput()
{
    int dx = 0, dy = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dy -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dy += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dx -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dx += 1;

    if (dx == 0 && dy == 0)
        return false;

    processVelocity(dx, dy);
    return true;
}
