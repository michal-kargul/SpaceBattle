#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Entity.h"
#include <iostream>

class Game
{
public:
    Game();
    void run();
    static std::vector<std::unique_ptr<Entity>> entities;

private:
    void render();
    void processEvents();

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    void handlePlayerInput(const sf::Event::KeyPressed* key);

    template<typename T>
    bool InList(const T& value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
};
