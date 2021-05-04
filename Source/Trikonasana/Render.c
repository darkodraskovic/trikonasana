#include "Display.h"
#include "Render.h"
#include "Trikonasana/Mesh.h"
#include "Trini/Matrix.h"

unsigned int TRI_renderMask = RM_POINT | RM_WIRE | RM_SOLID;

void TRI_AddRenderMode(enum RenderMode rm) {
    TRI_renderMask |= rm;
}

void TRI_RemoveRenderMode(enum RenderMode rm) {
    TRI_renderMask ^= rm;
}

void TRI_ToggleRenderMode(enum RenderMode rm) {
    if (TRI_renderMask & rm) TRI_renderMask ^= rm;
    else TRI_renderMask |= rm;
}

int Tri_CullBackface(Vec3f campPos, Vec3f facePos, Vec3f normal) {
    Vec3f camRay = vec3fSub(campPos, facePos);
    return vec3fDot(camRay, normal) < 0;
}

/* Vec2f Tri_ProjectOrtho(Vec3f point) { */
/*     float x = point.x * fovFactor + (float)windowWidth / 2; */
/*     float y = point.y * fovFactor + (float)windowHeight / 2; */
/*     Vec2f projectedPoint = {.x = x, .y = y}; */
/*     return projectedPoint; */
/* } */

Vec4f Tri_ProjectPerspective(Vec4f point) {
    Vec4f projPt = mat4MulVec4(TRI_projectionMatrix, point);

    if (projPt.w) {
        projPt.x /= projPt.w;
        projPt.y /= projPt.w;
        projPt.z /= projPt.w;
    }
    
    return projPt;
}
