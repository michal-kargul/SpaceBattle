#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Entity.h"
#include "Particle.h"
#include "Codes.h"
#include "Texture.h"

class Game
{
public:
    Game();
    void run();

private:
    void render();
    void update(float deltaTime);
    void processEvents();
    void handlePlayerInput();
    void processCameraZoom();
    void loadTextures();
    sf::Vector2f getCenterCameraPosition() const;

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    sf::View view;
    std::unique_ptr<sf::Sprite> backgroundSprite;
    sf::Vector2u mapSize;

    std::map<TextureType, Texture> loadedTextures;
    std::vector<Player> players;
    std::vector<Particle> particles;
    std::vector<Ship> ships;

    bool steeringButtonPressed = false;
    float currentZoom = 1.0f;

};
