#include <math.h>
#include "Vector.h"

Vec3f rotateVec3fX(const Vec3f* v, float angle) {
    Vec3f result = {
        .x = v->x,
        .y = v->y * cos(angle) - v->z * sin(angle),
        .z = v->y * sin(angle) + v->z * cos(angle),
    };
    return result;
}

Vec3f rotateVec3fY(const Vec3f* v, float angle) {
    Vec3f result = {
        .x = v->x * cos(angle) - v->z * sin(angle),
        .y = v->y,
        .z = v->x * sin(angle) + v->z * cos(angle),
    };
    return result;
}

Vec3f rotateVec3fZ(const Vec3f* v, float angle) {
    Vec3f result = {
        .x = v->x * cos(angle) - v->y * sin(angle),
        .y = v->x * sin(angle) + v->y * cos(angle),
        .z = v->z,
    };
    return result;
}

