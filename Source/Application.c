#include "Application.h"
#include "Renderer/Display.h"

bool isRunning = false;

void initApp() {
    isRunning = initializeWindow();
    initializeColorBuffer();
    
    start();
}

void runApp(){
    initApp();

    while (isRunning) {
        processInput();
        update();
        render();
    }
    
    destroyWindow();
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
