#include "Particle.h"

Particle::Particle(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const sf::Sprite& relativeSprite, const float offsetX, const float offsetY)
    : Entity(textures, maxVelocity, acceleration), relativeSprite(&relativeSprite), offsetX(offsetX), offsetY(offsetY)
{
    setSprite().setPosition(relativeSprite.getPosition());
    setSprite().setOrigin({ static_cast<float>(getSprite().getTexture().getSize().x) / 2 - relativeSprite.getTexture().getSize().x / 2 + offsetX, static_cast<float>(getSprite().getTexture().getSize().y) / 2 - relativeSprite.getTexture().getSize().y/2 + offsetY});
}

Particle::Particle(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const float curVelocityX, const float curVelocityY, sf::Vector2f position)
    : Entity(textures, maxVelocity, acceleration)
{
    setSprite().setOrigin({ static_cast<float>(getSprite().getTexture().getSize().x) / 2, static_cast<float>(getSprite().getTexture().getSize().y) / 2});
    setSprite().setPosition(position);
}

const float Particle::calculateAngle(const sf::Vector2<float>&, const sf::RenderWindow&)
{
    return 0.f;
}

void Particle::rotate(const float angle)
{
    if (relativeSprite != nullptr)
        setSprite().setRotation(relativeSprite->getRotation());
    else
        setSprite().setRotation(sf::degrees(angle));
}

void Particle::move()
{
    if (relativeSprite != nullptr)
        setSprite().setPosition(relativeSprite->getPosition());
    else if (curVelocityX || curVelocityY)
    {
        setSprite().move({curVelocityX, curVelocityY});
    }
}