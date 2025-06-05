#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

public:
    std::vector<Player> players;
    std::vector<Particle> particles;
    std::vector<Ship> ships;
private:
    void render();
    void update(float deltaTime);
    void processEvents();
    void handlePlayerInput();
    void processCameraZoom();
    void loadTextures();
    const sf::Vector2f getAveragePosition() const;

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    sf::View view;
    sf::Sprite* backgroundSprite;
    sf::Vector2u mapSize;
    std::map<TextureType, Texture> loadedTextures;

    bool steeringButtonPressed = false;
    
    template<typename T>
    bool InList(const T& value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
};
