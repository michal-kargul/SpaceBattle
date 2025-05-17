#include "Game.h"
#include <iostream>

std::vector<Entity> Game::entities;

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    entities.emplace_back("PlayerBlue_Frame");
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
            //update(mTimePerFrame);
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
//
//void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
//    if (key == sf::Keyboard::W)      mIsMovingUp = isPressed;
//    else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
//    else if (key == sf::Keyboard::A) mIsMovingLeft = isPressed;
//    else if (key == sf::Keyboard::D) mIsMovingRight = isPressed;
//}
//
//void Game::update(sf::Time deltaTime) {
//    sf::Vector2f movement(0.f, 0.f);
//    if (mIsMovingUp)    movement.y -= 100.f;
//    if (mIsMovingDown)  movement.y += 100.f;
//    if (mIsMovingLeft)  movement.x -= 100.f;
//    if (mIsMovingRight) movement.x += 100.f;
//}

void Game::render()
{
    mWindow.clear();

    for (const auto& entity : entities)
    {
        mWindow.draw(entity.getSprite());
    }
    mWindow.display();
}
