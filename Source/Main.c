#include <stdio.h>
#include <stdint.h>
#include "Display.h"
#include "Draw.h"

bool is_running = false;

void processInput(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

void setup(void) {
    is_running = initializeWindow();
    initializeColorBuffer();    
}

void update(void) {
    drawGrid(0xFFFF0000, 0, 0, windowWidth, windowHeight, 10);
    drawRect(0xFFFF0000, 30, 30, 50, 100);
}

int main(int argc, char *argv[]){
    setup();

    while (is_running) {
        processInput();
        update();
        render();
    }

    destroyWindow();

    return 0;
}
