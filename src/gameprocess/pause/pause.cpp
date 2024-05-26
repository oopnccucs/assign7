#include "pause.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

// add your code to implement the Pause class here

// ACTION_INIT is a state where nothing has been input.












void Pause::render() {
    AnsiPrint("\n\n\n\n\n\n\n\n\n", black, black);
    AnsiPrint("                             -- Pause --\n\n", white, black);
    AnsiPrint("                      Press any key to continue.", white, black);
    AnsiPrint("\n\n\n\n\n\n\n\n", black, black);
}