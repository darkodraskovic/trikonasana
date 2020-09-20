#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

void drawGrid(uint32_t color, int x, int y, int width, int height, int distance);
void drawRect(uint32_t color, int x, int y, int width, int height);

#endif /* DRAW_H */
