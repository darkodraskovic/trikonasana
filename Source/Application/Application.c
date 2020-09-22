#include "Application.h"
#include "Graphics/Display.h"

bool isRunning = false;

void initApp() {
    isRunning = initWindow();
    initColorBuffer();
}

void runApp(){
    initApp();
    start();

    while (isRunning) {
        processInput();
        
        input();
        update();
        draw();
        
        render();
    }

    stop();
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
