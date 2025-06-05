#include "Player.h"

Player::Player(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration)
    : Ship(textures, maxVelocity, acceleration)
{
}

const bool Player::handleMovementInput()
{
    dx = 0, dy = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dy -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dy += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dx -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dx += 1;

    if (dx == 0 && dy == 0)
        return false;

    processVelocity(dx, dy);
    return true;
}
