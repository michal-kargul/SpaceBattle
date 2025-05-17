#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <algorithm>

class Entity {
public:
    Entity(const std::string& textureName);
    virtual ~Entity();

    const sf::Sprite& getSprite() const;
    virtual void handleInput(const sf::Event::KeyPressed* key) = 0;

private:
    std::string textureName;
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    std::vector<sf::Texture> textures;
};
