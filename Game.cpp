#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    mWindow.setFramerateLimit(100);

    players.emplace_back("PlayerBlue_Frame", 8, 0.4);
    players.at(0).setSprite().setPosition({ 100,200 });
    particles.emplace_back("Exhaust_Frame", 8, 0.4, players.at(0).getSprite(), 32, -2);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    view.setCenter({960,540}); // œrodek widoku
    view.setSize({1920, 1080});   // rozmiar widoku

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > mTimePerFrame) {
            timeSinceLastUpdate -= mTimePerFrame;

            handlePlayerInput();
            processEvents();
            update(dt.asSeconds());
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
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadPlus)
                view.zoom(1.1);
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadMinus)
                view.zoom(0.9);
        }
    }
}

void Game::handlePlayerInput()
{
    steeringButtonPressed = players.at(0).handleMovementInput();
}

void Game::update(float deltaTime)
{
    for (auto& player : players)
    {
        if (!steeringButtonPressed)
        {
            player.processVelocity();
            //
        }

        player.rotate(player.calculateAngle(player.getSprite().getPosition(), mWindow));
        player.move();
        player.animate(player.getTextureVector(), player.setSprite(), 0.07f, deltaTime); 
    }

    for (auto& particle : particles)
    {
        particle.rotate();
        particle.move();
        particle.animate(particle.getTextureVector(), particle.setSprite(), 0.07f, deltaTime);
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.setView(view);

    for (auto& player : players)
    {
        mWindow.draw(player.getSprite());
    }

    for (auto& particle : particles)
    {
        mWindow.draw(particle.getSprite());
    }
    mWindow.display();
}
