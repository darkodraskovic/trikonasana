#include <math.h>

#include "Display.h"

void initBuffers();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;;
SDL_Texture *renderTexture = NULL;

color_t* renderBuffer = NULL;;
color_t* clearBuffer = NULL;;

int windowWidth = 640;
int windowHeight = 400;
int pixelSize = 2;

size_t bufferSize;
size_t pitch;

Mat4 TRI_projectionMatrix;

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

    TRI_projectionMatrix = mat4Perspective(M_PI / 3, (float)windowHeight / windowWidth, 0.1, 100);

    return true;
};


void initBuffers() {
    bufferSize = windowWidth * windowHeight * sizeof(color_t);
    pitch = windowWidth * sizeof(color_t);

    renderBuffer = (color_t*)malloc(sizeof(color_t) * windowWidth * windowHeight);
    clearBuffer = (color_t*)malloc(sizeof(color_t) * windowWidth * windowHeight);
    Tri_SetClearColor(0x000000FF);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

void Tri_SetClearColor(color_t color) {
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
