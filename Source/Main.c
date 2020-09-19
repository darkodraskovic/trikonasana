#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_running = false;

SDL_Window* window;
SDL_Renderer *renderer;

SDL_Texture *colorBufferTexture;
uint32_t *colorBuffer;

int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  };

  SDL_DisplayMode display_mode;
  SDL_GetDisplayMode(0, 0, &display_mode);

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

void setup(void) {
  colorBuffer = (uint32_t *)malloc(sizeof(Uint32) * windowWidth * windowHeight);
  colorBufferTexture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch(event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

void update(void) {}

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
    clearColorBuffer(0xFFFFFF00);

    SDL_RenderPresent(renderer);
}

void destroyWindow(void) {
  free(colorBuffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]){

  is_running = initializeWindow();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
    }

    destroyWindow();

    return 0;
}
