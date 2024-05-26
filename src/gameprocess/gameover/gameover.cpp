#include "gameover.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

GameOver::GameOver() {
}

GameOver::~GameOver() {
}

ProcessInfo GameOver::run(InputState action) {
    return CONTINUE;
}

void GameOver::render() {
    AnsiPrint("\n\n\n\n\n\n\n\n\n", black, black);
    AnsiPrint("                              Game Over ", red, black);
    AnsiPrint("\n\n\n\n\n\n\n\n\n\n", black, black);
}