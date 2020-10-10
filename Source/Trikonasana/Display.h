#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

extern uint32_t *colorBuffer;
extern uint32_t clearColor;

extern int windowWidth;
extern int windowHeight;

bool Tri_InitWindow(void);
void Tri_InitColorBuffer(void);

void Tri_Render(void);
void Tri_DestroyWindow(void);

#endif /* DISPLAY_H */
