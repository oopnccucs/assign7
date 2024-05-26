#include <iostream>

#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

#include "../gameprocess/allgameprocess.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    RoomData roomData = ROOM_DATA[defaultRoomIndex];
    Room *room = new Room(roomData);
    rooms.insert(std::pair<int, Room *>(defaultRoomIndex, room));
    currentRoomIndex = defaultRoomIndex;
    player = new Player(roomData.playerInitialPosition);

    state = PROCESS_MOVEMENT;
    currentProcess = new Move(player, room);
}

Controller::~Controller() {
    for (size_t i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
    delete player;
}

RunningState Controller::run(InputState action) {

    if(state == PROCESS_GAMEOVER) {
        return EXIT;
    }

    if(state == PROCESS_GAMECLEAR) {
        return EXIT;
    }

    ProcessInfo info = currentProcess->run(action);

    // add your code to implement process control



















    this->render();

    return PLAY;
}

// Add your code to implement the Controller class here.















// render
void Controller::render() {
    currentProcess->render();
    output();
}