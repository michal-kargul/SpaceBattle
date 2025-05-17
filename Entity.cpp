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
    switch (deltaX)
    {
    case -1:
    {
        curVelocityX = curVelocityX - acceleration;
        break;
    }
    case 1:
    {
        curVelocityX = curVelocityX + acceleration;
        break;
    }
    default:
        if (curVelocityX)
        {
            if (curVelocityX > 0)
            {
                if (curVelocityX <= acceleration / 10)
                    curVelocityX = 0;
                else
                    curVelocityX = curVelocityX - (acceleration / 10);
            }
            else
            {
                if (curVelocityX >= acceleration / 10 * -1)
                    curVelocityX = 0;
                else
                    curVelocityX = curVelocityX + (acceleration / 10);
            }
        }
        break;
    }

    switch (deltaY)
    {
    case -1:
    {
        curVelocityY = curVelocityY - acceleration;
        break;
    }
    case 1:
    {
        curVelocityY = curVelocityY + acceleration;
        break;
    }
    default:
        if (curVelocityY > 0)
        {
            if (curVelocityY <= acceleration / 10)
                curVelocityY = 0;
            else
                curVelocityY = curVelocityY - (acceleration / 10);
        }
        else
        {
            if (curVelocityY >= acceleration / 10 * -1)
                curVelocityY = 0;
            else
                curVelocityY = curVelocityY + (acceleration / 10);
        }
        break;
    }
}
