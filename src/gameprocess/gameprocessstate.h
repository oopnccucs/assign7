#ifndef GAMEPROCESSSTATE_H
#define GAMEPROCESSSTATE_H

namespace GameProcess
{
    enum GameProcessState {
        PROCESS_MOVEMENT,
        PROCESS_PAUSE,
        PROCESS_BATTLE,
        PROCESS_GAMEOVER,
        PROCESS_GAMECLEAR,
        PROCESS_EXIT
    };

    enum ProcessInfo {
        CONTINUE,
        
        MOVE_FINISH_ROOMCHANGE_LEFT,
        MOVE_FINISH_ROOMCHANGE_RIGHT,
        MOVE_FINISH_PAUSE,
        MOVE_FINISH_BATTLE,

        PAUSE_FINISH,

        BATTLE_FINISH_PLAYER_WIN,
        BATTLE_FINISH_PLAYER_DEAD,
    };
} // namespace GameProcess


#endif