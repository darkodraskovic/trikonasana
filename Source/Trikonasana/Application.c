#include "Application.h"
#include "Display.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

bool running = false;

SDL_Event TRI_event;
    
Uint32 previousFrame = 0;
float msPerUpdate = 1000.f / 60;

void initApp() {
    running = Tri_InitDisplay();
}

void processInput(void) {
    SDL_PollEvent(&TRI_event);

    switch (TRI_event.type) {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        if (TRI_event.key.keysym.sym == SDLK_ESCAPE)
            running = false;
        break;
    }
}

void Tri_RunApp(){
    initApp();
    start();

    while (running) {
        int waitTime = msPerUpdate - (SDL_GetTicks() - previousFrame);
        if (waitTime > 0) {
            SDL_Delay(waitTime);
        }
        previousFrame = SDL_GetTicks();

        processInput();
        input();

        update();

        draw();
        Tri_Render();
    }

    stop();
    Tri_DestroyDisplay();
}
