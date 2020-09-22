#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

void drawPixel(int x, int y, uint32_t color);
void drawGrid(uint32_t color, int x, int y, int width, int height, int distance);
void drawRect(int x, int y, int width, int height, uint32_t color);

#endif /* DRAW_H */
