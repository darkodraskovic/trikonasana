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

