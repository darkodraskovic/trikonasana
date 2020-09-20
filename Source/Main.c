#include <stdio.h>
#include <stdint.h>
#include "Display.h"
#include "Draw.h"
#include "Application.h"
#include "Vector.h"

void start(void) {
    
}

void update(void) {
    drawGrid(0xFFFF0000, 0, 0, windowWidth, windowHeight, 10);
    drawPixel(windowWidth / 2, windowHeight / 2, 0xFF00FF00);
    drawRect(0xFFFF0000, 30, 30, 50, 100);
}

int main(int argc, char *argv[]){
    runApp();
    return 0;
}
