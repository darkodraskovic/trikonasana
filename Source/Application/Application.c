#include "Application.h"
#include "Graphics/Display.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

bool isRunning = false;

/* Uint32 elapsedTime = 0; */
Uint32 previousFrame = 0;
Uint32 frameLag = 0;
float msPerUpdate = 1000 / 60;

void initApp() {
    isRunning = initWindow();
    initColorBuffer();
}

void runApp(){
    initApp();
    start();

    while (isRunning) {
        /* Uint32 timeout = elapsedTime + deltaTime; */
        /* while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) { */
        /*     // lock execution */
        /* }; */
        /* elapsedTime = SDL_GetTicks(); */
        
        Uint32 current = SDL_GetTicks();
        Uint32 elapsed = current - previousFrame;
        previousFrame = current;
        frameLag += elapsed;
        
        processInput();
        input();

        while (frameLag >= msPerUpdate) {
            update();
            frameLag -= msPerUpdate;
        }
        
        draw();
        render();
    }

    stop();
    destroyWindow();
}

void setFPS(int fps) {
    fps = fps;
    msPerUpdate = 1000.0 / fps;
}

void processInput(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        break;
    }    
}
