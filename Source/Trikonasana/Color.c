#include "Color.h"

color_t BLACK = 0x000000FF;
color_t WHITE = 0xFFFFFFFF;
color_t GREY = 0x777777FF;
color_t RED = 0xFF0000FF;
color_t GREEN = 0x00FF00FF;
color_t BLUE = 0x0000FFFF;
color_t YELLOW = 0xFFFF00FF;
color_t MAGENTA = 0xFF00FFFF;
color_t CYAN = 0x00FFFFFF;

color_t Tri_SetColorBrightness(color_t color, float percent) {
    if (percent <= 0) return BLACK;
    // return RGB * percent  + alpha (don't affect alpha)
    color_t r = (color & COL_MASK_R) * percent;
    color_t g = (color & COL_MASK_G) * percent;
    color_t b = (color & COL_MASK_B) * percent;
    return (r & COL_MASK_R) | (g & COL_MASK_G) | (b & COL_MASK_B) | (color & COL_MASK_A);
}
