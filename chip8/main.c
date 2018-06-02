

#include <stdio.h>
#include "chip8.h"
#include "graphics8.h"

Chip8 myChip8;

int main(int argc, const char * argv[]) {

    FILE  *game_file = NULL;
    unsigned char status;
    if (argc > 0) {
            game_file = fopen(argv[0], "b");
    }
    else {
        game_file = DEFAULT_GAME;
    }

    initializeChip8(&myChip8, game_file);
    setupGraphics();
    setupInput();

    status = runChip8(&myChip8);


    return status;
}
