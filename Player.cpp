#include "Player.h"

Player::Player(const std::string& textureName)
    : Ship(textureName)
{
}

void Player::handleInput(const sf::Event::KeyPressed* key)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        std::cout << "UP";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        std::cout << "DOWN";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        std::cout << "LEFT";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        std::cout << "RIGHT";
}
