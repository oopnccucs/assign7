#include "room.h"
#include "roomdata.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

// read data to the Room class
Room::Room(RoomData data) {
    this->roomID = data.id;
    this->roomName = data.name;
    this->roomDescription = data.description;

    this->playerInitialPosition = data.playerInitialPosition;

    for(auto enemy : data.enemies) {
        this->enemies.push_back(enemy);
    }

    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            this->defaultRoomObjectMap[y][x] = RoomObject(data.defaultRoomObjectMap[y][x]);
        }
    }
}

// add your code to implement the Room class here

















// render
void Room::render(Position position) {
    switch(this->defaultRoomObjectMap[position.getY()][position.getX()]) {
        case OBJECT_NONE:
            AnsiPrint("  ", black, black);
            break;
        case OBJECT_DOOR:
            AnsiPrint("DR", yellow, black);
            break;
        case OBJECT_WALL:
            AnsiPrint("██", white, black);
            break;
        case OBJECT_GRASS:
            AnsiPrint("WW", green, black);
            break;
        case OBJECT_ROCK:
            AnsiPrint("▲▲", yellow, black);
            break;
        case OBJECT_WATER:
            if(rand() % 2 == 0) {
                AnsiPrint("~~", cyan, blue);
            } else {
                AnsiPrint("……", cyan, blue);
            }
            break;
    }
}