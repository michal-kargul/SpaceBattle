#include "Game.h"

std::vector<std::unique_ptr<Entity>> Game::entities;

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    Game::entities.push_back(std::make_unique<Player>("PlayerBlue_Frame", 200, 1));
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
            else
                handlePlayerInput(keyPressed);
        }
    }
}

void Game::handlePlayerInput(const sf::Event::KeyPressed* key)
{
    if (InList(key->scancode, { sf::Keyboard::Scancode::W , sf::Keyboard::Scancode::S , sf::Keyboard::Scancode::A , sf::Keyboard::Scancode::D }))
    {
        for (auto& entity : entities)
        {
            entity->handleMovementInput();
        }
        steeringButtonPressed = true;
    }
}

void Game::update()
{
    for (auto& entity : entities)
    {
        if (!steeringButtonPressed)
            entity->processVelocity();

        entity->move();
    }

    steeringButtonPressed = false;
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
