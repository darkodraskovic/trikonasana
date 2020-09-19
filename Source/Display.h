#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

extern SDL_Window* window;
extern SDL_Renderer *renderer;

extern SDL_Texture *colorBufferTexture;
extern uint32_t *colorBuffer;
extern uint32_t clearColor;

extern int windowWidth;
extern int windowHeight;

bool initializeWindow(void);
void renderColorBuffer(void);
void clearColorBuffer(uint32_t color);
void render(void);
void destroyWindow(void);
void initializeColorBuffer(void);

#endif /* DISPLAY_H */
