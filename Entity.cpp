#include "Entity.h"

Entity::Entity(const std::string& textureName, const float maxVelocity, const float acceleration)
    : textureName(textureName), maxVelocity(maxVelocity), acceleration(acceleration)
{
    const std::string folder = "assets/";
    const std::string prefix = textureName + "_";

    std::vector<std::filesystem::path> matchingPaths;

    for (const auto& entry : std::filesystem::directory_iterator(folder))
    {
        const auto& path = entry.path();
        const std::string filename = path.filename().string();

        if (filename.rfind(prefix, 0) == 0 && path.extension() == ".png")
            matchingPaths.push_back(path);
    }

    std::sort(matchingPaths.begin(), matchingPaths.end());

    for (const auto& path : matchingPaths)
    {
        sf::Texture tex;

        if (!tex.loadFromFile(path.string()))
        {
            std::cerr << "Couldn't load texture: " << path.string() << "\n";
            continue;
        }

        textures.push_back(std::move(tex));
    }

    if (textures.empty())
        throw std::runtime_error("Textures not found for: " + textureName);

    sprite.emplace(textures[0]);
}

Entity::~Entity() {}

const sf::Sprite& Entity::getSprite() const
{
    return *sprite;
}

void Entity::move()
{
    if (sprite && (curVelocityX || curVelocityY))
    {
        sprite->move({ curVelocityX, curVelocityY });
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
