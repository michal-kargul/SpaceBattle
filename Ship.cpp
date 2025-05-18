#include "Ship.h"

Ship::Ship(const std::string& textureName, const float maxVelocity, const float acceleration)
    : Entity(textureName, maxVelocity, acceleration)
{
    
}

const float Ship::calculateAngle(const sf::Vector2<float>& currPos, const sf::RenderWindow& relative)
{
    float x = sf::Mouse::getPosition(relative).x - currPos.x;
    float y = sf::Mouse::getPosition(relative).y - currPos.y;

    float angleRad = std::atan2(y, x);
    angleDeg = (angleRad * 180.f / 3.14159265f) + 90;

    if (angleDeg < 0.f)
        angleDeg += 360.f;

    return angleDeg;
}

void Ship::animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime)
{
    animationTimer += deltaTime;
    if (animationTimer < animationTime || textures.empty())
        return;

    animationTimer = 0.f;

    const int maxIndex = static_cast<int>(textures.size()) - 1;

    sf::Vector2f velocity(dx, dy);
    float angleRad = -angleDeg * 3.14159265f / 180.f;
    float localX = std::cos(angleRad) * velocity.x - std::sin(angleRad) * velocity.y;
    float localY = std::sin(angleRad) * velocity.x + std::cos(angleRad) * velocity.y;

    const bool isNotMoving = (std::abs(dx) < 0.01f && std::abs(dy) < 0.01f);
    const bool isMovingStraight = std::abs(localX) < 0.05f;
    const bool isTiltingLeft = localX < -0.1f;
    const bool isTiltingRight = localX > 0.1f;

    if (isNotMoving || isMovingStraight)
    {
        if (animateGameLoopIteration > 0)
            animateGameLoopIteration--;
        else
            animateGameLoopIteration = 0;

        sprite.setTexture(textures.at(animateGameLoopIteration));
        sprite.setScale(sf::Vector2f(1.f, 1.f));
    }
    else if (isTiltingLeft || isTiltingRight)
    {
        const float targetScaleX = isTiltingLeft ? 1.f : -1.f;
        const float currentScaleX = sprite.getScale().x;

        if ((isTiltingLeft && currentScaleX < 0.f) || (isTiltingRight && currentScaleX > 0.f))
        {
            if (animateGameLoopIteration > 0)
                animateGameLoopIteration--;
        }
        else
        {
            if (animateGameLoopIteration < maxIndex)
                animateGameLoopIteration++;
        }

        sprite.setTexture(textures.at(animateGameLoopIteration));
        sprite.setScale(sf::Vector2f(targetScaleX, 1.f));
    }
}
