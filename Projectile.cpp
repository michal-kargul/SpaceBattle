#include "Projectile.h"

Projectile::Projectile(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const float curVelocityX, const float curVelocityY, sf::Vector2f position)
    : Particle(textures, maxVelocity, acceleration, curVelocityX, curVelocityY, position)
{
    setSprite().setOrigin({ static_cast<float>(getSprite().getTexture().getSize().x) / 2, static_cast<float>(getSprite().getTexture().getSize().y) / 2 });
    setSprite().setPosition(position);
}