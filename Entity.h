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
    Entity(const std::string& textureName, const float maxVelocity, const float acceleration);
    virtual ~Entity();

    sf::Sprite& getSprite();
    void move();
    void rotate(const float angle);
    virtual const bool handleMovementInput() = 0;
    virtual const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) = 0;
    virtual void animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime) = 0;
    void processVelocity(const int deltaX = 0, const int deltaY = 0);
    const std::vector<sf::Texture>& getTextureVector() const;

protected:
    const float maxVelocity;
    float curVelocityX = 0;
    float curVelocityY = 0;
    const float acceleration;
    float animationTimer = 0.f;
    int animateGameLoopIteration = 0;

private:
    std::string textureName;
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    std::vector<sf::Texture> textures;
};
