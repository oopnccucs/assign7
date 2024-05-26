#ifndef MOVE_H
#define MOVE_H

#include "../gameprocess.h"
#include "../../gameobjects/player/player.h"
#include "../../gameobjects/room/room.h"

class Move: public GameProcessBase {
private:
    Player *player;
    
    Room *room;
    
public:
    Move(Player* player, Room* room);
    ~Move();

    ProcessInfo run(InputState action);

    void render();
};

#endif