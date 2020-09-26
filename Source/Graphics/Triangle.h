#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Math/Vector.h"

typedef struct {
    int a;
    int b;
    int c;
} Face;

typedef struct {
    Vec2 points[3];
} Tri2;

typedef struct {
    Vec3 points[3];
} Tri3;

#endif /* TRIANGLE_H */
