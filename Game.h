#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"

class Game
{
public:
    Game();
    void run();
    static std::vector<Entity> entities;

private:
    void render();
    void processEvents();

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
};
