#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

// Vec2i

char* vec2iToString(Vec2i* v) {
    char* str = malloc(sizeof(char) * 32);
    sprintf(str, "%d %d", v->x, v->y);
    return str;
}


// Vec2i

char* vec3iToString(Vec3i* v) {
    char* str = malloc(sizeof(char) * 32);
    sprintf(str, "%d %d %d", v->x, v->y, v->z);
    return str;
}

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

float vec2fDot(Vec2f v1, Vec2f v2) { return v1.x * v2.x + v1.y * v2.y; }

Vec2f* vec2fNormLocal(Vec2f* v) {
    float len = vec2fLen(*v);
    v->x /= len;
    v->y /= len;
    return v;
}

char* vec2fToString(Vec2f* v) {
    char* str = malloc(sizeof(char) * 32);
    sprintf(str, "%.2f %.2f", v->x, v->y);
    return str;
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

Vec3f* vec3fNormLocal(Vec3f* v) {
    float len = vec3fLen(*v);
    v->x /= len;
    v->y /= len;
    v->z /= len;
    return v;
}

char* vec3fToString(Vec3f* v) {
    char* str = malloc(sizeof(char) * 32);
    sprintf(str, "%.2f %.2f %.2f", v->x, v->y, v->z);
    return str;
}

// Conversion

Vec3f vec3FromVec4(Vec4f v) {
    return (Vec3f){v.x, v.y, v.z};
}

Vec4f vec4FromVec3(Vec3f v) {
    return (Vec4f){v.x, v.y, v.z, 1};
}
