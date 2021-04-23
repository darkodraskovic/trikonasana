#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// 0xRRGGBBAA
typedef uint32_t color_t;

#define COL_MASK_R 0xFF000000
#define COL_MASK_G 0x00FF0000
#define COL_MASK_B 0x0000FF00
#define COL_MASK_A 0x000000FF

#define BLACK (color_t)0x000000FF
#define WHITE (color_t)0xFFFFFFFF
#define GREY (color_t)0x777777FF
#define RED (color_t)0xFF0000FF
#define GREEN (color_t)0x00FF00FF
#define BLUE (color_t)0x0000FFFF
#define YELLOW (color_t)0xFFFF00FF
#define MAGENTA (color_t)0xFF00FFFF
#define CYAN (color_t)0x00FFFFFF

color_t Tri_SetColorBrightness(color_t color, float percent);

#endif /* COLOR_H */
