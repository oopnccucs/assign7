#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>

#include "enviroment.h"
#include "../gamecore/gamestate.h"
#include "../gameobjects/room/room.h"
#include "../gameobjects/player/player.h"
#include "../gameprocess/gameprocess.h"
#include "../gameprocess/gameprocessstate.h"

using namespace GameState;
using namespace GameProcess;

// The controller class is for handling the main game loop and logic.

class Controller {
private:
    std::map<int, Room *> rooms;
    int currentRoomIndex;

    Player *player;

    GameProcessState state;

    GameProcessBase *currentProcess;

    void roomChange(int roomIndex);

    void stateChange(GameProcessState newState);

public:
    Controller();
    ~Controller();

    // main game loop function
    RunningState run(InputState action);

    void render();
};

#endif