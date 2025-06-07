#include "Player.h"

Player::Player(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const PlayerControl playerType)
    : Ship(textures, maxVelocity, acceleration), playerType(playerType)
{
}

const bool Player::handleMovementInput()
{
    dx = 0, dy = 0;

    switch (playerType)
    {
    case PlayerControl::PLAYER_1:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dy -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dy += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dx -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dx += 1;
        break;
    case PlayerControl::PLAYER_2:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) dy -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) dy += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) dx -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dx += 1;
        break;
    }
        

    if (dx == 0 && dy == 0)
        return false;

    processVelocity(dx, dy);
    return true;
}
