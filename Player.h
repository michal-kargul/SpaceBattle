#pragma once

#include "Ship.h"

class Player : public Ship {
public:
    Player(const std::string& textureName, const float maxVelocity, const float acceleration);

    const bool handleMovementInput() override;
private:
    
};
