#include "Ship.h"

Ship::Ship(const std::string& textureName, const float maxVelocity, const float acceleration)
    : Entity(textureName, maxVelocity, acceleration)
{
    
}

const float Ship::calculateAngle(const sf::Vector2f& currPos, const sf::RenderWindow& relative)
{
    sf::Vector2f mouseWorld = relative.mapPixelToCoords(sf::Mouse::getPosition(relative));

    float x = mouseWorld.x - currPos.x;
    float y = mouseWorld.y - currPos.y;

    float angleRad = std::atan2(y, x);
    angleDeg = (angleRad * 180.f / 3.14159265f) + 90.f;

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

    float speed = std::sqrt(dx * dx + dy * dy);
    float sideIntensity = (speed > 0.01f) ? (localX / speed) : 0.f;
    float intensityAbs = std::abs(sideIntensity);

    float targetScaleX = (sideIntensity < 0.f) ? 1.f : -1.f;
    int targetIndex = static_cast<int>(std::round(intensityAbs * maxIndex));
    targetIndex = std::clamp(targetIndex, 0, maxIndex);

    float currentScaleX = sprite.getScale().x;

    static bool reversingDirection = false;

    if (currentScaleX != targetScaleX && !reversingDirection)
    {
        reversingDirection = true;
    }

    if (reversingDirection)
    {
        if (animateGameLoopIteration > 0)
        {
            animateGameLoopIteration--;
        }
        else
        {
            sprite.setScale(sf::Vector2f(targetScaleX, 1.f));
            reversingDirection = false;
        }

        sprite.setTexture(textures.at(animateGameLoopIteration));
        return;
    }

    if (animateGameLoopIteration < targetIndex)
    {
        animateGameLoopIteration++;
    }
    else if (animateGameLoopIteration > targetIndex)
    {
        animateGameLoopIteration--;
    }

    sprite.setTexture(textures.at(animateGameLoopIteration));
}
