#pragma once

#include "Ship.h"
#include "Codes.h"

class Player : public Ship {
public:
    Player(const std::vector<sf::Texture>& textures, const float maxVelocity, const float acceleration, const PlayerControl playerType);

    const bool handleMovementInput();
private:
    PlayerControl playerType;
};
