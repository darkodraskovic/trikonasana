#ifndef RENDER_H
#define RENDER_H

#include "Trini/Vector.h"

extern unsigned int TRI_renderMask;

enum RenderMode {
    RM_POINT = 1, RM_WIRE = 2, RM_SOLID = 4,
};

enum CullMode { CM_NONE, CM_BACK, CM_FRONT } TRI_cullMode = CM_BACK;

void TRI_AddRenderMode(enum RenderMode rm);
void TRI_RemoveRenderMode(enum RenderMode rm);
void TRI_ToggleRenderMode(enum RenderMode rm);

int Tri_CullBackface(Vec3f campPos, Vec3f a, Vec3f b, Vec3f c);
Vec2f Tri_ProjectOrtho(Vec3f point);
Vec2f Tri_ProjectPerspective(Vec3f campPos, Vec3f point);

#endif /* RENDER_H */
