#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode({ 1920, 1080 }), "Space Battle")
    , mTimePerFrame(sf::seconds(1.f / 60.f))
{
    loadTextures();

    mWindow.setFramerateLimit(100);

    const sf::Texture& backgroundTex = loadedTextures.at(BACKGROUND).getTextures().back();
    backgroundSprite = std::make_unique<sf::Sprite>(backgroundTex);

    mapSize = backgroundTex.getSize();
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

    ships.emplace_back(loadedTextures[SHIP_RED].getTextures(), 8, 0.4);

    players.emplace_back(loadedTextures[SHIP_BLUE].getTextures(), 8, 0.4, PlayerControl::PLAYER_1);
    players.emplace_back(loadedTextures[SHIP_BLUE].getTextures(), 8, 0.4, PlayerControl::PLAYER_2);

    for (const auto& player : players)
        particles.emplace_back(loadedTextures[SHIP_EXHAUST].getTextures(), 8, 0.4, player.getSprite(), 32, -2);

    for (const auto& ship : ships)
        particles.emplace_back(loadedTextures[SHIP_EXHAUST].getTextures(), 8, 0.4, ship.getSprite(), 32, -2);
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

void Game::loadTextures()
{
    for (const auto& [type, name] : textureMap)
    {
        std::cout << "Loading texture: " << name << std::endl;

        Texture tex(name);
        loadedTextures.emplace(type, std::move(tex));
    }
}

void Game::processCameraZoom()
{
    const float innerMargin = 300.f;
    const float outerMargin = 100.f;

    sf::Vector2f windowSize(
        static_cast<float>(mWindow.getSize().x),
        static_cast<float>(mWindow.getSize().y)
    );
    sf::Vector2f viewSize = windowSize * currentZoom;

    sf::Vector2f center = getCenterCameraPosition();

    bool outsideOuter = false;
    bool insideInner = true;

    auto checkMargins = [&](const sf::Vector2f& pos, bool affectsZoomOut)
        {
            float dx = std::abs(pos.x - center.x);
            float dy = std::abs(pos.y - center.y);

            if (affectsZoomOut)
            {
                if (dx > (viewSize.x / 2.f - outerMargin) || dy > (viewSize.y / 2.f - outerMargin))
                    outsideOuter = true;
            }

            if (dx > (viewSize.x / 2.f - innerMargin) || dy > (viewSize.y / 2.f - innerMargin))
                insideInner = false;
        };

    for (const auto& player : players)
        checkMargins(player.getSprite().getPosition(), true);

    for (const auto& ship : ships)
        checkMargins(ship.getSprite().getPosition(), true);

    float targetZoom = currentZoom;

    if (outsideOuter && view.getSize().x < mapSize.x)
        targetZoom *= 1.02f;
    else if (insideInner && currentZoom > 1.01f)
        targetZoom *= 0.98f;

    targetZoom = std::clamp(targetZoom, 1.0f, 3.0f);

    float smoothing = 0.17f;
    currentZoom += (targetZoom - currentZoom) * smoothing;

    view.setSize(windowSize * currentZoom);

    float halfWidth = view.getSize().x / 2.f;
    float halfHeight = view.getSize().y / 2.f;

    float leftLimit = -static_cast<float>(mapSize.x) / 2.f + halfWidth;
    float rightLimit = static_cast<float>(mapSize.x) / 2.f - halfWidth;
    float topLimit = -static_cast<float>(mapSize.y) / 2.f + halfHeight;
    float bottomLimit = static_cast<float>(mapSize.y) / 2.f - halfHeight;

    if (leftLimit <= rightLimit)
        center.x = std::clamp(center.x, leftLimit, rightLimit);
    else
        center.x = (leftLimit + rightLimit) / 2.f;

    if (topLimit <= bottomLimit)
        center.y = std::clamp(center.y, topLimit, bottomLimit);
    else
        center.y = (topLimit + bottomLimit) / 2.f;

    view.setCenter(center);
}

sf::Vector2f Game::getCenterCameraPosition() const
{
    float sumPosX = 0.f;
    float sumPosY = 0.f;
    size_t count = 0;

    for (const auto& player : players)
    {
        sumPosX += player.getSprite().getPosition().x;
        sumPosY += player.getSprite().getPosition().y;
        ++count;
    }

    for (const auto& ship : ships)
    {
        sumPosX += ship.getSprite().getPosition().x;
        sumPosY += ship.getSprite().getPosition().y;
        ++count;
    }

    if (count == 0)
        return { 0.f, 0.f };

    return { sumPosX / count, sumPosY / count };
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
    for (auto& player : players)
        steeringButtonPressed = player.handleMovementInput();
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

    for (auto& ship : ships)
    {
        mWindow.draw(ship.getSprite());
    }

    for (auto& particle : particles)
    {
        mWindow.draw(particle.getSprite());
    }
    mWindow.display();
}
