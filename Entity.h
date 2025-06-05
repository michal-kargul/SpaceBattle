#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <functional>  // <== DODANE

class Entity {
public:
    Entity(const std::vector<sf::Texture>& textures, float maxVelocity, float acceleration);
    virtual ~Entity();

    const sf::Sprite& getSprite() const;
    sf::Sprite& setSprite();
    const sf::Vector2f& getVelocity() const;
    virtual void move();
    virtual void rotate(const float angle);

    virtual const float calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative) = 0;
    virtual void animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime);
    void processVelocity(const int deltaX = 0, const int deltaY = 0);
    const std::vector<sf::Texture>& getTextureVector() const;

    bool isAlive = true;

protected:
    const float maxVelocity;
    float curVelocityX = 0;
    float curVelocityY = 0;
    float angleDeg = 0;
    const float acceleration;
    float animationTimer = 0.f;
    int animateGameLoopIteration = 0;

private:
    std::string textureName;
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

    std::reference_wrapper<const std::vector<sf::Texture>> textures;
};
