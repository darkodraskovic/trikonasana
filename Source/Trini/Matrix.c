#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Vector.h"

Mat4 mat4Identity(void) {
    Mat4 m = {{1, 0, 0, 0},
              {0, 1, 0, 0},
              {0, 0, 1, 0},
              {0, 0, 0, 1},};
    return m;
}

Mat4 mat4Scale(float sx, float sy, float sz) {
    Mat4 m = mat4Identity();
    m.m0.x = sx;
    m.m1.y = sy;
    m.m2.z = sz;
    return m;
}

Mat4 mat4Translate(float tx, float ty, float tz) {
    Mat4 m = mat4Identity();
    m.m0.w = tx;
    m.m1.w = ty;
    m.m2.w = tz;
    return m;
}

Mat4 mat4RotateX(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m1.y = c; m.m1.z = -s;
    m.m2.y = s; m.m2.z = c;
    return m;
}

Mat4 mat4RotateY(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m0.x = c; m.m0.z = s;
    m.m2.x = -s; m.m2.z = c;
    return m;
}

Mat4 mat4RotateZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 m = mat4Identity();
    m.m0.x = c; m.m0.y = -s;
    m.m1.x = s; m.m1.y = c;
    return m;
}

Vec3f mat4MulVec3(Mat4 m, Vec3f v) {
    return vec3FromVec4(mat4MulVec4(m, vec4FromVec3(v)));
}

Vec4f mat4MulVec4(Mat4 m, Vec4f v) {
    Vec4f result;
    result.x = vec4fDot(m.m0, v);
    result.y = vec4fDot(m.m1, v);
    result.z = vec4fDot(m.m2, v);
    result.w = vec4fDot(m.m3, v);
    return result;
}

Mat4 mat4Transpose(Mat4 src) {
    Mat4 dst;
    float* srcp = (float*)&src;
    float* dstp = (float*)&dst;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            dstp[j*4 + i] = srcp[i*4 + j];
        }
    }
    return dst;
}

Mat4 mat4MulMat4(Mat4 m1, Mat4 m2) {
    Mat4 ret;
    m2 = mat4Transpose(m2);
    
    ret.m0.x = vec4fDot(m1.m0, m2.m0);
    ret.m0.y = vec4fDot(m1.m0, m2.m1);
    ret.m0.z = vec4fDot(m1.m0, m2.m2);
    ret.m0.w = vec4fDot(m1.m0, m2.m3);

    ret.m1.x = vec4fDot(m1.m1, m2.m0);
    ret.m1.y = vec4fDot(m1.m1, m2.m1);
    ret.m1.z = vec4fDot(m1.m1, m2.m2);
    ret.m1.w = vec4fDot(m1.m1, m2.m3);

    ret.m2.x = vec4fDot(m1.m2, m2.m0);
    ret.m2.y = vec4fDot(m1.m2, m2.m1);
    ret.m2.z = vec4fDot(m1.m2, m2.m2);
    ret.m2.w = vec4fDot(m1.m2, m2.m3);

    ret.m3.x = vec4fDot(m1.m3, m2.m0);
    ret.m3.y = vec4fDot(m1.m3, m2.m1);
    ret.m3.z = vec4fDot(m1.m3, m2.m2);
    ret.m3.w = vec4fDot(m1.m3, m2.m3);

    return ret;
}
