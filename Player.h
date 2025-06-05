#pragma once

#include "Ship.h"

class Player : public Ship {
public:
    Player(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration);

    const bool handleMovementInput();
private:
    
};
