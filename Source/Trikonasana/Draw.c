#include "Draw.h"

void swapInt(int* n1, int* n2) {
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

// PIXEL

void Tri_DrawPixel(int x, int y, color_t color) {
    if (x > -1 && x < windowWidth && y > -1 && y < windowHeight)
        renderBuffer[windowWidth * y + x] = color;
}

// LINE

void Tri_DrawLineHorizontal(int x0, int y0, int x1, color_t color) {
    if (x0 > x1) swapInt(&x0, &x1);
    int idx = windowWidth * y0 + x0;
    int end = windowWidth * y0 + x1;
    while (idx <= end) renderBuffer[idx++] = color;
}

void Tri_DrawLine(int x0, int y0, int x1, int y1, color_t color) {
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    float sideLen = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);

    float incX = deltaX / sideLen;
    float curX = x0;
    float incY = deltaY / sideLen;
    float curY = y0;

    for (int i = 0; i < sideLen; ++i) {
        Tri_DrawPixel(curX, curY, color);
        curX += incX;
        curY += incY;
    }
}

// TRIANGLE

void Tri_DrawTri(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    Tri_DrawLine(x0, y0, x1, y1, color);
    Tri_DrawLine(x1, y1, x2, y2, color);
    Tri_DrawLine(x2, y2, x0, y0, color);
}

//      (x0,y0)
//        /\
//       /  \
// (x1,y1)--(Mx,My)
void drawFlatBottom(int x0, int y0, int x1, int y1, int Mx, int My, color_t color) {
    float m1 = (float)(x1 - x0) / (y1 - y0); // reciprocal slope (inverse)
    float m2 = (float)(Mx - x0) / (My - y0);
    float xStart = x0, xEnd = x0;
    for (int y = y0; y <= y1; y++) { // loop scanlines from top to bottom
        Tri_DrawLineHorizontal(xStart, y, xEnd, color);
        xStart += m1; xEnd += m2;
    }
}

// (x1, y1)--(Mx, My)
//      \  /
//       \/
//    (x2,y2)
void drawFlatTop(int x1, int y1, int Mx, int My, int x2, int y2, color_t color) {
    float m1 = (float)(x1 - x2) / (y2 - y1); // reciprocal slope (inverse)
    float m2 = (float)(Mx - x2) / (y2 - My);
    float xStart = x2, xEnd = x2;
    for (int y = y2; y >= y1; y--) { // loop scanlines from top to bottom
        Tri_DrawLineHorizontal(xStart, y, xEnd, color);
        xStart += m1; xEnd += m2;
    }
}

void Tri_DrawTriSolid(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    // sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        swapInt(&y0, &y1);
        swapInt(&x0, &x1);
    }
    if (y1 > y2) {
        swapInt(&y1, &y2);
        swapInt(&x1, &x2);
    }
    if (y0 > y1) {
        swapInt(&y0, &y1);
        swapInt(&x0, &x1);
    }

    // prevent division by 0 and redundant draw
    if (y1 == y2) {
        drawFlatBottom(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        drawFlatTop(x0, y0, x1, y1, x2, y2, color);
    } else {
        int Mx = ((float)((x2 - x0) * (y1 - y0))) / (float)(y2 - y0) + x0;
        // My = y1
        drawFlatBottom(x0, y0, x1, y1, Mx, y1, color);
        drawFlatTop(x1, y1, Mx, y1, x2, y2, color);
    }
}

// RECT

void Tri_DrawGrid(int x, int y, int width, int height, int distance, color_t color) {
    for (int j = y; j < height; j += distance) {
        for (int i = x; i < width; i += distance) {
            Tri_DrawPixel(i, j, color);
        }
    }
};

void Tri_DrawRect(int x, int y, int width, int height, color_t color) {
    for (int j = y; j < y + height; j ++) {
        for (int i = x; i < x + width; i ++) {
            Tri_DrawPixel(i, j, color);
        }
    }
};
