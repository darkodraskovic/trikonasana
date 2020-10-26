#include "Display.h"
#include <SDL2/SDL_rect.h>
#include <string.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;;

SDL_Texture* colorBufferTexture = NULL;;
uint32_t* colorBuffer = NULL;;
uint32_t clearColor = 0x000000FF;

int windowWidth = 640;
int windowHeight = 400;
int pixelSize = 2;

bool Tri_InitWindow(void) {
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

    return true;
};


void Tri_InitColorBuffer(void) {
    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

void renderColorBuffer(void) {
    SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer, windowWidth * sizeof(uint32_t));
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void clearColorBuffer(uint32_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void Tri_Render(void) {
    renderColorBuffer();
    clearColorBuffer(clearColor);

    SDL_RenderPresent(renderer);
}

void Tri_DestroyWindow(void) {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
