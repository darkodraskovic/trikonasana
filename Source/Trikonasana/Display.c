#include "Display.h"
#include <SDL2/SDL_rect.h>
#include <stdint.h>
#include <string.h>

void initBuffers();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;;
SDL_Texture *renderTexture = NULL;

uint32_t* renderBuffer = NULL;;
uint32_t* clearBuffer = NULL;;

int windowWidth = 640;
int windowHeight = 400;
int pixelSize = 2;

size_t bufferSize;
size_t pitch;

bool Tri_InitDisplay() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    };

    window = SDL_CreateWindow(NULL, 0, 0, windowWidth * pixelSize, windowHeight * pixelSize,
                              SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    initBuffers();

    return true;
};


void initBuffers() {
    bufferSize = windowWidth * windowHeight * sizeof(uint32_t);
    pitch = windowWidth * sizeof(uint32_t);

    renderBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    clearBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    Tri_SetClearColor(0x000000FF);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

void Tri_SetClearColor(uint32_t color) {
    int i = 0;
    while (i < windowWidth * windowHeight) clearBuffer[i++] = color;
}

void Tri_Render(void) {
    // renderBuffer -> renderTexture
    SDL_UpdateTexture(renderTexture, NULL, renderBuffer, pitch);

    // renderTexture -> renderer -> rendering target
    // srcrect: NULL for the entire texture; dstrect: NULL for the entire rendering target
    // => if pixelSize > 1 then scale up texture (to "nearest" => pixelated)
    SDL_RenderCopy(renderer, renderTexture, NULL, NULL);

    // clear renderBuffer
    memcpy(renderBuffer, clearBuffer, bufferSize);

    // render target -> screen
    SDL_RenderPresent(renderer);
}

void Tri_DestroyDisplay() {
    free(renderBuffer);
    free(clearBuffer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
