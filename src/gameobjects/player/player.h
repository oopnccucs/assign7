#ifndef PLAYER_H
#define PLAYER_H

#include "../../gamecore/gamestate.h"
#include "../gameobject.h"
#include "playerstate.h"

using namespace PlayerState;

class Player: public GameObject {
    int healPower = 8;
public:
    Player(Position initialPosition);
    ~Player();

    // move player to the position and return move result to determine the next state
    MoveState move(InputState action);

    // To enhance gameplay, a player healing option has been added.
    void heal(int amount);
    int getHealPower();
    
    void render();
};

#endif