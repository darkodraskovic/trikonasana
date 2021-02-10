#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

extern uint32_t *renderBuffer;

extern int windowWidth;
extern int windowHeight;
extern int pixelSize;

bool Tri_InitDisplay(void);
void Tri_InitColorBuffer(void);

void Tri_Render(void);
void Tri_DestroyDisplay(void);

void Tri_SetClearColor(uint32_t color);

#endif /* DISPLAY_H */
