#include "Trini/Vector.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_TRIS (6 * 2) // 6 cube faces, 2 triangles per face

Vec3f cubeVertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 0
    { .x = -1, .y =  1, .z = -1 }, // 1
    { .x =  1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y = -1, .z = -1 }, // 3
    { .x =  1, .y =  1, .z =  1 }, // 4
    { .x =  1, .y = -1, .z =  1 }, // 5
    { .x = -1, .y =  1, .z =  1 }, // 6
    { .x = -1, .y = -1, .z =  1 }  // 7
};                                 

Vec3i cubeTris[N_CUBE_TRIS] = {
    // front
    { .x = 0, .y = 1, .z = 2 },
    { .x = 0, .y = 2, .z = 3 },
    // right
    { .x = 3, .y = 2, .z = 4 },
    { .x = 3, .y = 4, .z = 5 },
    // back
    { .x = 5, .y = 4, .z = 6 },
    { .x = 5, .y = 6, .z = 7 },
    // left
    { .x = 7, .y = 6, .z = 1 },
    { .x = 7, .y = 1, .z = 0 },
    // top
    { .x = 1, .y = 6, .z = 4 },
    { .x = 1, .y = 4, .z = 2 },
    // bottom
    { .x = 5, .y = 7, .z = 0 },
    { .x = 5, .y = 0, .z = 3 }
};
