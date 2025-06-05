#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(const std::string& textureName) : textureName(textureName)
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
        std::cerr << "Textures not found for: " << textureName << "\n";
}

const std::vector<sf::Texture>& Texture::getTextures() const
{
    return textures;
}
