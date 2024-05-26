#ifndef GAMESTSATE_H
#define GAMESTSATE_H

namespace GameState {
    enum RunningState {
        PLAY,
        EXIT
    };

    enum InputState {
        ACTION_NONE,
        ACTION_UP,
        ACTION_DOWN,
        ACTION_LEFT,
        ACTION_RIGHT,
        ACTION_CONFIRM,
        ACTION_PAUSE,
        ACTION_EXIT,
        ACTION_INIT
    };
} // namespace Gamestate

#endif