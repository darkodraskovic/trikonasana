#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 rotateVec3X(Vec3 v, float angle);
Vec3 rotateVec3Y(Vec3 v, float angle);
Vec3 rotateVec3Z(Vec3 v, float angle);

#endif /* VECTOR_H */
