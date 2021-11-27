#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "Color.h"
#include "Trini/Matrix.h"

extern SDL_Renderer* Tri_renderer;
extern color_t* renderBuffer;

extern int windowWidth;
extern int windowHeight;
extern int pixelSize;

extern Mat4 TRI_projectionMatrix;
extern Mat4 TRI_screenMatrix;

bool Tri_InitDisplay(void);
void Tri_InitColorBuffer(void);

void Tri_Render(void);
void Tri_DestroyDisplay(void);

void Tri_SetClearColor(color_t color);

#endif /* DISPLAY_H */
