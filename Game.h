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

private:
    void render();
    void update(float deltaTime);
    void processEvents();
    void handlePlayerInput();

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    bool steeringButtonPressed = false;

    sf::View view;

    template<typename T>
    bool InList(const T& value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
};
