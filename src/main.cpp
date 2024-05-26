#include <iostream>
#include <thread>

#include <chrono> // for sleep function
#include <ctime>
#include <cstdlib>
#include <csignal>

#include <unistd.h>
#include <termios.h>
#include <iostream>

#include "gamecore/gamecore.h"

static struct termios old_termios, new_termios;

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}

int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

static int exit_loop;

void signal_handler(__attribute__((unused)) int signum) {
    exit_loop = 1;
}

int main(int argc, char *argv[]) {
    // initial setup
    std::cin.tie(0)->sync_with_stdio(0);
    configure_terminal();
    signal(SIGINT, signal_handler);
    // initial setup end

    GameCore game;

    GameState::RunningState state = GameState::PLAY;

    // init state
    int input = -1;

    srand(time(NULL));

    clock_t start, end;

    while (state != GameState::EXIT && !exit_loop) {

        start = clock();

        GameState::InputState action = GameCore::ConvertInputToAction(input);

        // main game loop entry point
        state = game.lifeCycle(action);
        
        input = read_input();

        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPEED) continue;
        int time = int((SPEED - time_taken) * 1000); // 0.1 seconds
        if(time > 0) std::this_thread::sleep_for(std::chrono::milliseconds(time)); // frame delay
        
    }

    return 0;
    
}
