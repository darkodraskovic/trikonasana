#ifndef DRAW_H
#define DRAW_H

#include "Math/Vector.h"
#include <stdint.h>

void drawPixel(int x, int y, uint32_t color);

void drawGrid(uint32_t color, int x, int y, int width, int height, int distance);
void drawRect(int x, int y, int width, int height, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
void drawTri(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif /* DRAW_H */
