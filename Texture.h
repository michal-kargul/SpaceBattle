#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

class Texture
{
public:
    Texture();
    Texture(const std::string& textureName);

    // Move allowed
    Texture(Texture&&) noexcept = default;
    Texture& operator=(Texture&&) noexcept = default;

    // Copy forbidden
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    const std::vector<sf::Texture>& getTextures() const;

private:
    std::string textureName;
    std::vector<sf::Texture> textures;
};