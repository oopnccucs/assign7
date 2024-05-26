#include "gamecore.h"
#include "gamestate.h"
#include "../controller/controller.h"

GameCore::GameCore() {
    
}

GameCore::~GameCore() {
    
}

RunningState GameCore::lifeCycle(InputState action) {
    return gameController.run(action);
}

InputState GameCore::ConvertInputToAction(int input) {
    switch (input) {
        case 'w':
        case 'W':
            return ACTION_UP;
        case 's':
        case 'S':
            return ACTION_DOWN;
        case 'a':
        case 'A':
            return ACTION_LEFT;
        case 'd':
        case 'D':
            return ACTION_RIGHT;

        case 32: // space
            return ACTION_CONFIRM;
        case 10: // enter
            return ACTION_CONFIRM;

        case 27: // esc
            return ACTION_PAUSE;

        case -1:
            return ACTION_INIT;

        default:
            return ACTION_NONE;
    }
}