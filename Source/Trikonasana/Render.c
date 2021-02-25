#include "Display.h"
#include "Render.h"

int fovFactor = 512;
unsigned int rmMask = RM_WIRE|RM_SOLID;

void TRI_SetRenderMode(enum RenderMode rm) {
    rmMask |= rm;
}

unsigned int TRI_GetRenderMode(enum RenderMode rm) {
    return rmMask & rm;
}

void TRI_ToggleRenderMode(enum RenderMode rm) {
    if (rmMask & rm) rmMask ^= rm;
    else rmMask |= rm;
}

int Tri_CullBackface(Vec3f campPos, Vec3f a, Vec3f b, Vec3f c) {
    Vec3f ab = vec3fSub(b, a);
    Vec3f ac = vec3fSub(c, a);
    Vec3f norm = vec3fCross(ab, ac);
    Vec3f camRay = vec3fSub(campPos, a);
    return vec3fDot(camRay, norm) < 0;
}

Vec2f Tri_ProjectOrtho(Vec3f point) {
    float x = point.x * fovFactor + (float)windowWidth / 2;
    float y = point.y * fovFactor + (float)windowHeight / 2;
    Vec2f projectedPoint = {.x = x, .y = y};
    return projectedPoint;
}

Vec2f Tri_ProjectPerspective(Vec3f campPos, Vec3f point) {
    point.z -= campPos.z;
    float x = point.x / point.z;
    x = x * fovFactor + (float)windowWidth / 2;
    float y = point.y / point.z;
    y = y * fovFactor + (float)windowHeight / 2;
    return (Vec2f){.x = x, .y = y};
}
