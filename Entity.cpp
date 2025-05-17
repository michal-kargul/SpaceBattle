#include "Entity.h"

Entity::Entity(const std::string& textureName)
    : textureName(textureName)
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

const sf::Sprite& Entity::getSprite() const
{
    return *sprite;
}
