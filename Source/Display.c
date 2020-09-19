#include "Display.h"

SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;;

SDL_Texture *colorBufferTexture = NULL;;
uint32_t *colorBuffer = NULL;;
uint32_t clearColor = 0xFF000000;

int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    };

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    windowWidth = display_mode.w * 0.5;
    windowHeight = display_mode.h * 0.5;
  
    window = SDL_CreateWindow(NULL, 0, 0, windowWidth, windowHeight,
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


void initializeColorBuffer(void) {
    colorBuffer = (uint32_t *)malloc(sizeof(Uint32) * windowWidth * windowHeight);
    colorBufferTexture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

void renderColorBuffer(void) {
    SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer,
                      (int)windowWidth * sizeof(uint32_t));
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void clearColorBuffer(uint32_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderColorBuffer();
    clearColorBuffer(clearColor);

    SDL_RenderPresent(renderer);
}

void destroyWindow(void) {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
