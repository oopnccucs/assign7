#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

using namespace PlayerState;

Player::Player(Position initialPosition): GameObject(initialPosition, 20, 2, "Player") {
}

// Add your code to implement the Player class here.







// render
void Player::render() {
    AnsiPrint("PL", green, blue);
}

