#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

typedef struct {
    float m[3][3];
} Mat3;

typedef struct {
    float m[4][4];
} Mat4;

Mat3 mat3Identity(void);
Vec3f mat3MulVec3(Mat3 m, Vec3f v);
Mat3 mat3Screen(int scrWidth, int scrHeight);

Mat4 mat4Identity(void);
Vec4f mat4MulVec4(Mat4 m, Vec4f v);
Mat4 mat4MulMat4(Mat4 m1, Mat4 m2);

Mat4 mat4Scale(float sx, float sy, float sz);
Mat4 mat4Translate(float tx, float ty, float tz);
Mat4 mat4RotateX(float angle);
Mat4 mat4RotateY(float angle);
Mat4 mat4RotateZ(float angle);
Mat4 mat4Perspective(float fov, float aspect, float near, float far);

#endif /* MATRIX_H */
