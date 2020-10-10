#include "Draw.h"
#include "Display.h"
#include <stdint.h>
#include <stdlib.h>

void drawPixel(int x, int y, uint32_t color) {
    if (x > -1 && x < windowWidth && y > -1 && y < windowHeight)
        colorBuffer[windowWidth * y + x] = color;
}

void drawGrid(uint32_t color, int x, int y, int width, int height, int distance) {
    for (int j = y; j < height; j += distance) {
        for (int i = x; i < width; i += distance) {
            drawPixel(i, j, color);
        }
    }
};

void drawRect(int x, int y, int width, int height, uint32_t color) {
    for (int j = y; j < y + height; j ++) {
        for (int i = x; i < x + width; i ++) {
            drawPixel(i, j, color);
        }
    }
};

void drawLine(int x0, int y0, int x1, int y1, uint32_t color) {
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    float sideLen = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);

    float incX = deltaX / sideLen;
    float curX = x0;    
    float incY = deltaY / sideLen;
    float curY = y0;

    for (int i = 0; i < sideLen; ++i) {
        drawPixel(curX, curY, color);
        curX += incX;
        curY += incY;
    }
}

void drawTri(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}
