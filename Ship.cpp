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

void Ship::processShipState()
{
    directions[NOT_MOVING] = dy == 0 && dx == 0;
    directions[MOVING_UP] = dy < 0;
    directions[MOVING_DOWN] = dy > 0;
    directions[MOVING_LEFT] = dx < 0;
    directions[MOVING_RIGHT] = dx > 0;

    directions[HEADING_UP] = (angleDeg >= 315 || angleDeg < 45);
    directions[HEADING_RIGHT] = (angleDeg >= 45 && angleDeg < 135);
    directions[HEADING_DOWN] = (angleDeg >= 135 && angleDeg < 225);
    directions[HEADING_LEFT] = (angleDeg >= 225 && angleDeg < 315);

    directions[SAME_MOVING_DIRECTIONS] =
        (directions[MOVING_UP] && (directions[HEADING_UP] || directions[HEADING_DOWN]))
        || (directions[MOVING_DOWN] && (directions[HEADING_DOWN] || directions[HEADING_UP]))
        || (directions[MOVING_RIGHT] && (directions[HEADING_RIGHT] || directions[HEADING_LEFT]))
        || (directions[MOVING_LEFT] && (directions[HEADING_LEFT] || directions[HEADING_RIGHT]));

    directions[TILT_LEFT] = 
        (directions[HEADING_UP] && directions[MOVING_LEFT])
        || (directions[HEADING_RIGHT] && directions[MOVING_UP])
        || (directions[HEADING_DOWN] && directions[MOVING_RIGHT])
        || (directions[HEADING_LEFT] && directions[MOVING_DOWN]);

    directions[TILT_RIGHT] =
        (directions[HEADING_UP] && directions[MOVING_RIGHT])
        || (directions[HEADING_RIGHT] && directions[MOVING_DOWN])
        || (directions[HEADING_DOWN] && directions[MOVING_LEFT])
        || (directions[HEADING_LEFT] && directions[MOVING_UP]);
}

void Ship::animate(const std::vector<sf::Texture>& textures, sf::Sprite& sprite, float animationTime, float deltaTime)
{
    processShipState();
    animationTimer += deltaTime;

    if (animationTimer < animationTime)
        return;

    animationTimer = 0.f;

    const int maxIndex = static_cast<int>(textures.size()) - 1;

    if (directions[NOT_MOVING] || directions[SAME_MOVING_DIRECTIONS])
    {
        if (animateGameLoopIteration > 0)
            animateGameLoopIteration--;
        else
            animateGameLoopIteration = 0;

        sprite.setTexture(textures.at(animateGameLoopIteration));
        sprite.setScale(sf::Vector2f(1.f, 1.f));
    }
    else if (directions[TILT_LEFT] || directions[TILT_RIGHT])
    {
        const bool isTiltingLeft = directions[TILT_LEFT];
        const float targetScaleX = isTiltingLeft ? 1.f : -1.f;
        const float currentScaleX = sprite.getScale().x;

        if ((isTiltingLeft && currentScaleX < 0.f) || (!isTiltingLeft && currentScaleX > 0.f))
        {
            if (animateGameLoopIteration > 0)
                animateGameLoopIteration--;
        }
        else
        {
            if (animateGameLoopIteration < static_cast<int>(textures.size()) - 1)
                animateGameLoopIteration++;
        }

        sprite.setTexture(textures.at(animateGameLoopIteration));
        sprite.setScale(sf::Vector2f(targetScaleX, 1.f));
    }
}