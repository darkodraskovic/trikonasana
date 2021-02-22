#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

void Tri_DrawPixel(int x, int y, uint32_t color);

void Tri_DrawGrid(int x, int y, int width, int height, int distance, uint32_t color);
void Tri_DrawRect(int x, int y, int width, int height, uint32_t color);
void Tri_DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void Tri_DrawTri(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void Tri_DrawTriSolid(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif /* DRAW_H */
