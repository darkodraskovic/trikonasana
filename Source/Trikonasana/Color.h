#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// 0xRRGGBBAA
typedef uint32_t color_t;

#define COL_MASK_R 0xFF000000
#define COL_MASK_G 0x00FF0000
#define COL_MASK_B 0x0000FF00
#define COL_MASK_A 0x000000FF

extern color_t BLACK;
extern color_t WHITE;
extern color_t GREY;
extern color_t RED;
extern color_t GREEN;
extern color_t BLUE;
extern color_t YELLOW;
extern color_t MAGENTA;
extern color_t CYAN;

color_t Tri_SetColorBrightness(color_t color, float percent);

#endif /* COLOR_H */
