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

Vec3f rotateVec3fX(const Vec3f* v, float angle);
Vec3f rotateVec3fY(const Vec3f* v, float angle);
Vec3f rotateVec3fZ(const Vec3f* v, float angle);

#endif /* VECTOR_H */
