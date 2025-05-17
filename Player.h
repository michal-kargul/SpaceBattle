#pragma once

#include "Ship.h"

class Player : public Ship {
public:
    Player(const std::string& textureName);

    void handleInput(const sf::Event::KeyPressed* key) override;
private:
    
};
