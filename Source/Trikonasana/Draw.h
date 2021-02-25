#ifndef DRAW_H
#define DRAW_H

#include "Display.h"

void Tri_DrawPixel(int x, int y, color_t color);

void Tri_DrawGrid(int x, int y, int width, int height, int distance, color_t color);
void Tri_DrawRect(int x, int y, int width, int height, color_t color);
void Tri_DrawLine(int x0, int y0, int x1, int y1, color_t color);
void Tri_DrawTri(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
void Tri_DrawTriSolid(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

#endif /* DRAW_H */
