#include "slime.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Slime::Slime(Position initialPosition): Enemy(initialPosition, 5, 1, "Slime") {
}

// add your code to implement the Slime class here














// render function

void Slime::render() {
    AnsiPrint("==", yellow, green);
}
