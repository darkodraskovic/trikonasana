#ifndef RENDER_H
#define RENDER_H

#include "Trikonasana/Mesh.h"
#include "Trini/Matrix.h"
#include "Trini/Vector.h"

extern unsigned int TRI_renderMask;

enum RenderMode {
  RM_POINT = 1,
  RM_WIRE = 2,
  RM_SOLID = 4,
  RM_TEXTURE = 8,
};

enum CullMode { CM_NONE, CM_BACK, CM_FRONT };
extern enum CullMode TRI_cullMode;

void TRI_AddRenderMode(enum RenderMode rm);
void TRI_RemoveRenderMode(enum RenderMode rm);
void TRI_ToggleRenderMode(enum RenderMode rm);

int Tri_CullBackface(Vec3f campPos, Vec3f facePos, Vec3f normal);
Vec2f Tri_ProjectOrtho(Vec3f point);
Vec4f Tri_ProjectPerspective(Vec4f point);

#endif /* RENDER_H */
