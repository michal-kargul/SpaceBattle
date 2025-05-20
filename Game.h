#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Entity.h"
#include "Particle.h"
#include <iostream>

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
    const sf::Vector2f getAveragePosition() const;

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    sf::View view;
    sf::Texture backgroundTexture;
    sf::Sprite* backgroundSprite;
    sf::Vector2u mapSize;
    sf::Vector2f averagePosition;

    bool steeringButtonPressed = false;
    
    template<typename T>
    bool InList(const T& value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
};
