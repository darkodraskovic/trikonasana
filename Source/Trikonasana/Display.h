#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "Typedef.h"

extern color_t *renderBuffer;

extern int windowWidth;
extern int windowHeight;
extern int pixelSize;

bool Tri_InitDisplay(void);
void Tri_InitColorBuffer(void);

void Tri_Render(void);
void Tri_DestroyDisplay(void);

void Tri_SetClearColor(color_t color);

#endif /* DISPLAY_H */
