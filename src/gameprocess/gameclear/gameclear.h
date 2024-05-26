#ifndef GAMECLEAR_H
#define GAMECLEAR_H

#include "../gameprocess.h"

class GameClear: public GameProcessBase {
private:
    
public:
    GameClear();
    ~GameClear();

    ProcessInfo run(InputState action);

    void render();
};

#endif