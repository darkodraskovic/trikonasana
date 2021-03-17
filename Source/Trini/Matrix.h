#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

typedef struct {
    Vec4f m0, m1, m2, m3;
} Mat4;

Mat4 mat4Identity(void);
Mat4 mat4Scale(float sx, float sy, float sz);
Mat4 mat4Translate(float tx, float ty, float tz);
    
Vec3f mat4MulVec3(Mat4 m, Vec3f v);
Vec4f mat4MulVec4(Mat4 m, Vec4f v);

#endif /* MATRIX_H */
