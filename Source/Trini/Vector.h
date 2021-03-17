#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    int x, y, z;
} Vec3i;

typedef struct {
    float x, y;
} Vec2f;

typedef struct {
    float x, y, z;
} Vec3f;

typedef struct {
    float x, y, z, w;
} Vec4f;

char *vec2iToString(Vec2i *v);
char *vec3iToString(Vec3i *v);

float vec2fLen(Vec2f v);
Vec2f vec2fAdd(Vec2f v1, Vec2f v2);
Vec2f vec2fSub(Vec2f v1, Vec2f v2);
Vec2f vec2fMul(Vec2f v, float s);
Vec2f vec2fDiv(Vec2f v, float s);
float vec2fDot(Vec2f v1, Vec2f v2);
Vec2f* vec2fNormLocal(Vec2f* v);
char *vec2fToString(Vec2f *v);

float vec3fLen(Vec3f v);
Vec3f vec3fAdd(Vec3f v1, Vec3f v2);
Vec3f vec3fSub(Vec3f v1, Vec3f v2);
Vec3f vec3fMul(Vec3f v, float s);
Vec3f vec3fDiv(Vec3f v, float s);
Vec3f vec3fCross(Vec3f v1, Vec3f v2);
float vec3fDot(Vec3f v1, Vec3f v2);
Vec3f *vec3fNormLocal(Vec3f* v);
char* vec3fToString(Vec3f* v);

Vec3f rotateVec3fX(const Vec3f* v, float angle);
Vec3f rotateVec3fY(const Vec3f* v, float angle);
Vec3f rotateVec3fZ(const Vec3f* v, float angle);

float vec4fDot(Vec4f v1, Vec4f v2);

Vec3f vec3FromVec4(Vec4f v);
Vec4f vec4FromVec3(Vec3f v);

#endif /* VECTOR_H */
