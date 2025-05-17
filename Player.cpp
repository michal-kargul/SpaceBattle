#include "Player.h"

Player::Player(const std::string& textureName, const float maxVelocity, const float acceleration)
    : Ship(textureName, maxVelocity, acceleration)
{
}

void Player::handleMovementInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            processVelocity(-1, -1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            processVelocity(1, -1);
        else
            processVelocity(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            processVelocity(-1, 1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            processVelocity(1, 1);
        else
            processVelocity(0, 1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            processVelocity(-1, -1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            processVelocity(-1, 1);
        else
            processVelocity(-1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            processVelocity(1, -1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            processVelocity(1, 1);
        else
            processVelocity(1, 0);
    }
}
