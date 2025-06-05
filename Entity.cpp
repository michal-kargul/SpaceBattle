#include "Entity.h"

Entity::Entity(const std::vector<sf::Texture>& textures, float maxVelocity, float acceleration)
    : textures(textures), maxVelocity(maxVelocity), acceleration(acceleration)
{
    if (textures.empty())
        throw std::runtime_error("Textures not found");

    const auto& baseTexture = textures.at(0);
    sprite.emplace(baseTexture);

    sprite->setOrigin({
        static_cast<float>(baseTexture.getSize().x) / 2.f,
        static_cast<float>(baseTexture.getSize().y) / 2.f
        });
}

Entity::~Entity() {}

const sf::Sprite& Entity::getSprite() const
{
    return *sprite;
}

sf::Sprite& Entity::setSprite()
{
    return *sprite;
}

const sf::Vector2f& Entity::getVelocity() const
{
    return { curVelocityX, curVelocityY };
}

void Entity::move()
{
    if (sprite && (curVelocityX || curVelocityY))
    {
        sprite->move({ curVelocityX, curVelocityY });
    }
}

void Entity::rotate(const float angle)
{
    if (sprite && (sprite->getRotation().asDegrees()) != angle)
    {
        sprite->setRotation(sf::degrees(angle));
    }
}

void Entity::processVelocity(const int deltaX, const int deltaY)
{
    constexpr float accelFactor = 1.005f;
    constexpr float decelFactor = 0.99f;

    switch (deltaX)
    {
    case 1: 
        curVelocityX = std::min(curVelocityX * accelFactor + acceleration, maxVelocity);
        break;
    case -1:
        curVelocityX = std::max(curVelocityX * accelFactor - acceleration, -maxVelocity);
        break;
    default:
        curVelocityX *= decelFactor;
        if (std::abs(curVelocityX) < 0.01f)
            curVelocityX = 0.f;
        break;
    }

    switch (deltaY)
    {
    case 1: 
        curVelocityY = std::min(curVelocityY * accelFactor + acceleration, maxVelocity);
        break;
    case -1:
        curVelocityY = std::max(curVelocityY * accelFactor - acceleration, -maxVelocity);
        break;
    default:
        curVelocityY *= decelFactor;
        if (std::abs(curVelocityY) < 0.01f)
            curVelocityY = 0.f;
        break;
    }

    if (curVelocityX != 0.f && curVelocityY != 0.f)
    {
        float speed = std::sqrt(curVelocityX * curVelocityX + curVelocityY * curVelocityY);
        if (speed > maxVelocity)
        {
            float factor = maxVelocity / speed;
            curVelocityX *= factor;
            curVelocityY *= factor;
        }
    }

}

const std::vector<sf::Texture>& Entity::getTextureVector() const
{
    return textures;
}

void Entity::animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= animationTime)
    {
        animationTimer = 0.f;

        sprite.setTexture(textures.at(animateGameLoopIteration));

        animateGameLoopIteration++;
        if (animateGameLoopIteration >= textures.size())
            animateGameLoopIteration = 0;
    }
}
