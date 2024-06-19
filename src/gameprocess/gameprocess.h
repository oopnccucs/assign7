#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include "../gamecore/gamestate.h"
#include "../gameobjects/player/player.h"
#include "../gameobjects/room/room.h"

#include "gameprocessstate.h"

using namespace GameState;
using namespace GameProcess;

class GameProcessBase {
public:
    GameProcessBase();
    virtual ~GameProcessBase();

    // the only function that calls the process running
    virtual ProcessInfo run(InputState action) = 0;

    virtual void render() = 0;
};

#endif