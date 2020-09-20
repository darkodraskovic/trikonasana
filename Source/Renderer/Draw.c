#include "Draw.h"
#include "Display.h"

void drawGrid(uint32_t color, int x, int y, int width, int height, int distance) {
    for (int j = y; j < height; j += distance) {
        for (int i = x; i < width; i += distance) {
            colorBuffer[windowWidth * j + i] = color;
        }
    }
};

void drawRect(uint32_t color, int x, int y, int width, int height) {
    for (int j = y; j < y + height; j ++) {
        for (int i = x; i < x + width; i ++) {
            colorBuffer[windowWidth * j + i] = color;
        }
    }
};
