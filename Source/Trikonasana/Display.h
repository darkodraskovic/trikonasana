#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "Trini/Matrix.h"
#include "Color.h"

extern color_t *renderBuffer;

extern int windowWidth;
extern int windowHeight;
extern int pixelSize;

extern Mat4 TRI_projectionMatrix;

bool Tri_InitDisplay(void);
void Tri_InitColorBuffer(void);

void Tri_Render(void);
void Tri_DestroyDisplay(void);

void Tri_SetClearColor(color_t color);

#endif /* DISPLAY_H */
