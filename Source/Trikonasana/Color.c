#include "Color.h"

color_t Tri_SetColorBrightness(color_t color, float percent) {
    if (percent < 0) return 0x000000 | (color & COL_MASK_A);
    if (percent > 1) return color;
    
    // return RGB * percent  + alpha (don't affect alpha)
    color_t r = (color & COL_MASK_R) * percent;
    color_t g = (color & COL_MASK_G) * percent;
    color_t b = (color & COL_MASK_B) * percent;
    return (r & COL_MASK_R) | (g & COL_MASK_G) | (b & COL_MASK_B) | (color & COL_MASK_A);
}
