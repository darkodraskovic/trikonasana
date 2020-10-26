#include <math.h>
#include "Vector.h"

// Vec2f

float vec2fLen(Vec2f v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2f vec2fAdd(Vec2f v1, Vec2f v2) { return (Vec2f){v1.x + v2.x, v1.y + v2.y}; }

Vec2f vec2fSub(Vec2f v1, Vec2f v2) {
    return (Vec2f){v1.x - v2.x, v1.y - v2.y};
}

Vec2f vec2fMul(Vec2f v, float s) {
    return (Vec2f){v.x * s, v.y * s};
}

Vec2f vec2fDiv(Vec2f v, float s) {
    return (Vec2f){v.x / s, v.y / s};
}

float vec2fDot(Vec2f v1, Vec2f v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
// Vec3f

float vec3fLen(Vec3f v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3f vec3fAdd(Vec3f v1, Vec3f v2) {
    return (Vec3f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3f vec3fSub(Vec3f v1, Vec3f v2) {
    return (Vec3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec3f vec3fMul(Vec3f v, float s) {
    return (Vec3f){v.x * s, v.y * s, v.z * s};
}

Vec3f vec3fDiv(Vec3f v, float s) {
    return (Vec3f){v.x / s, v.y / s, v.z / s};
}

Vec3f vec3fCross(Vec3f v1, Vec3f v2) {
    return (Vec3f){ v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x };
}

float vec3fDot(Vec3f v1, Vec3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

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

