#pragma once

#include "Entity.h"
#include "Particle.h"

class Projectile : Particle
{
public:
	Projectile(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, float curVelocityX, const float curVelocityY, sf::Vector2f position);
};
