#include "Draw.h"
#include "Display.h"

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
