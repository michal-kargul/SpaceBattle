#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    mWindow.setFramerateLimit(100);

    if (!backgroundTexture.loadFromFile("assets/Nebula Blue.png"))
        std::cerr << "Couldn't load texture: " << "\n";

    backgroundSprite = new sf::Sprite(backgroundTexture);

    mapSize = backgroundTexture.getSize();
    backgroundSprite->setOrigin({
        static_cast<float>(mapSize.x) / 2.f,
        static_cast<float>(mapSize.y) / 2.f
        });

    backgroundSprite->setPosition({ 0.f, 0.f });

    sf::Vector2f windowSize = {
        static_cast<float>(mWindow.getSize().x),
        static_cast<float>(mWindow.getSize().y)
    };

    view.setSize(windowSize);
    view.setCenter({ 0.f, 0.f });
    mWindow.setView(view);

    players.emplace_back("PlayerBlue_Frame", 8, 0.4);
    particles.emplace_back("Exhaust_Frame", 8, 0.4, players.at(0).getSprite(), 32, -2);
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

            processCameraZoom();
            handlePlayerInput();
            processEvents();
            update(dt.asSeconds());
        }
        
        render();
    }
}

void Game::processCameraZoom()
{
    view.setCenter(getAveragePosition());
}

const sf::Vector2f Game::getAveragePosition() const
{
    float sumPosX=0;
    float sumPosY=0;

    for (const auto& player : players)
    {
        sumPosX += player.getSprite().getPosition().x;
        sumPosY += player.getSprite().getPosition().y;
    }

    for (const auto& ship : ships)
    {
        sumPosX += ship.getSprite().getPosition().x;
        sumPosY += ship.getSprite().getPosition().y;
    }

    //std::cout << "avg Pos: " << sumPosX / (ships.size() + players.size()) << " avg PosY: " << sumPosY / (ships.size() + players.size()) << std::endl;

    return { sumPosX / (ships.size() + players.size()) , sumPosY / (ships.size() + players.size())};
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
            player.processVelocity();

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
    mWindow.draw(*backgroundSprite);

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
