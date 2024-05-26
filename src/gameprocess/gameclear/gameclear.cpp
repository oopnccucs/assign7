#include "gameclear.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

GameClear::GameClear() {
}

GameClear::~GameClear() {
}

ProcessInfo GameClear::run(InputState action) {
    return CONTINUE;
}

void GameClear::render() {
    AnsiPrint("\n\n\n\n\n\n\n\n\n", black, black);
    AnsiPrint("                              Game Clear!", yellow, black);
    AnsiPrint("\n\n\n\n\n\n\n\n\n\n", black, black);
}