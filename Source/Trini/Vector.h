#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    int x;
    int y;
} Vec2i;

typedef struct {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct {
    float x;
    float y;
} Vec2f;

typedef struct {
    float x;
    float y;
    float z;
} Vec3f;

char *vec2iToString(Vec2i *v);
char *vec3iToString(Vec3i *v);

void vec2fSet(Vec2f* v, float x, float y);
float vec2fLen(Vec2f v);
Vec2f vec2fAdd(Vec2f v1, Vec2f v2);
Vec2f vec2fSub(Vec2f v1, Vec2f v2);
Vec2f vec2fMul(Vec2f v, float s);
Vec2f vec2fDiv(Vec2f v, float s);
float vec2fDot(Vec2f v1, Vec2f v2);
Vec2f* vec2fNormLocal(Vec2f* v);
char *vec2fToString(Vec2f *v);

void vec3fSet(Vec3f* v, float x, float y, float z);
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

#endif /* VECTOR_H */
