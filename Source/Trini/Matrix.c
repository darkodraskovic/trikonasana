#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Vector.h"

Mat4 mat4Identity(void) {
    Mat4 m = {
        {{1, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 1}},
    };
    return m;
}

Mat4 mat4Scale(float sx, float sy, float sz) {
    Mat4 m = mat4Identity();
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

Mat4 mat4Translate(float tx, float ty, float tz) {
    Mat4 m = mat4Identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}

Mat4 mat4RotateX(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m[1][1] = c; m.m[1][2] = -s;
    m.m[2][1] = s; m.m[2][2] = c;
    return m;
}

Mat4 mat4RotateY(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m[0][0] = c; m.m[0][2] = s;
    m.m[2][0] = -s; m.m[2][2] = c;
    return m;
}

Mat4 mat4RotateZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m[0][0] = c; m.m[0][1] = -s;
    m.m[1][0] = s; m.m[1][1] = c;
    return m;
}

Vec3f mat4MulVec3(Mat4 m, Vec3f v) {
    return vec3FromVec4(mat4MulVec4(m, vec4FromVec3(v)));
}

Vec4f mat4MulVec4(Mat4 m, Vec4f v) {
    Vec4f result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
    return result;
}

Mat4 mat4MulMat4(Mat4 m1, Mat4 m2) {
    Mat4 ret;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] +
                m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
        }
    }

    return ret;
}
