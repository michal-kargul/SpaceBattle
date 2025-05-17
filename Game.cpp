#include "Game.h"

std::vector<std::unique_ptr<Entity>> Game::entities;

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    mWindow.setFramerateLimit(100);
    Game::entities.push_back(std::make_unique<Player>("PlayerBlue_Frame", 8, 0.4));
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > mTimePerFrame) {
            timeSinceLastUpdate -= mTimePerFrame;

            handlePlayerInput();
            processEvents();
            update();
        }
        
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                mWindow.close();
        }
    }
}

void Game::handlePlayerInput()
{
    steeringButtonPressed = entities.at(0)->handleMovementInput();
}

void Game::update()
{
    for (auto& entity : entities)
    {
        if (!steeringButtonPressed)
            entity->processVelocity();

        entity->move();
    }
}

void Game::render()
{
    mWindow.clear();

    for (const auto& entity : entities)
    {
        mWindow.draw(entity->getSprite());
    }
    mWindow.display();
}
