#include "Vector.h"
#include <math.h>

Vec3 rotateVec3X(Vec3 v, float angle) {
    Vec3 result = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle),
    };
    return result;
}

Vec3 rotateVec3Y(Vec3 v, float angle) {
    Vec3 result = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle),
    };
    return result;
}

Vec3 rotateVec3Z(Vec3 v, float angle) {
    Vec3 result = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z,
    };
    return result;
}

