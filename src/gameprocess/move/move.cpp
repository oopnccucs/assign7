#include "move.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"

// Move the code from controller.cpp to this file, completing the Move Class


















void Move::render() {
    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            if(player->getPosition() == Position(x, y)) {
                player->render();
                continue;
            }
            bool flag = false;
            for(auto enemy : room->getEnemies()) {
                if(enemy->getPosition() == Position(x, y)) {
                    enemy->render();
                    flag = true;
                    continue;
                }
            }
            if(flag) continue;
            room->render(Position(x, y));
        }
    AnsiPrint("\n", nochange, nochange);
    }
}