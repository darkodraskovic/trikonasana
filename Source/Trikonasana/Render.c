#include "Render.h"

#include "Display.h"
#include "Trikonasana/Draw.h"
#include "Trikonasana/Mesh.h"
#include "Trini/Matrix.h"

unsigned int TRI_renderMask = RM_POINT | RM_WIRE | RM_SOLID;
enum CullMode TRI_cullMode = CM_BACK;

void TRI_AddRenderMode(enum RenderMode rm) { TRI_renderMask |= rm; }

void TRI_RemoveRenderMode(enum RenderMode rm) { TRI_renderMask ^= rm; }

void TRI_ToggleRenderMode(enum RenderMode rm) {
  if (TRI_renderMask & rm)
    TRI_renderMask ^= rm;
  else
    TRI_renderMask |= rm;
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

int Tri_CullBackface(Vec3f campPos, Vec3f facePos, Vec3f normal) {
  Vec3f camRay = vec3fSub(campPos, facePos);
  return vec3fDot(camRay, normal) < 0;
}

void Tri_SortFaces(Tri_Face* faces, int first, int last) {
  if (first >= last) return;

  int i, j, pivot;
  Tri_Face temp;
  pivot = first;
  i = first;
  j = last;

  while (i < j) {
    while (faces[i].depth <= faces[pivot].depth && i < last) i++;
    while (faces[j].depth > faces[pivot].depth) j--;
    if (i < j) {
      temp = faces[i];
      faces[i] = faces[j];
      faces[j] = temp;
    }
  }

  temp = faces[pivot];
  faces[pivot] = faces[j];
  faces[j] = temp;

  Tri_SortFaces(faces, first, j - 1);
  Tri_SortFaces(faces, j + 1, last);
}

void Tri_RenderFace(Tri_Face* face) {
  if (TRI_cullMode == CM_BACK && face->cull) {
    return;
  }

  Vec4f a = face->vertices[0];
  Vec4f b = face->vertices[1];
  Vec4f c = face->vertices[2];

  // render
  if (TRI_renderMask & RM_SOLID) {
    Tri_DrawTriSolid(a.x, a.y, b.x, b.y, c.x, c.y, face->color);
  }
  if (TRI_renderMask & RM_TEXTURE) {
    Tri_DrawTriTexture(a, b, c, face->uvs[0], face->uvs[1], face->uvs[2], face->texture);
  }
  if (TRI_renderMask & RM_WIRE) {
    Tri_DrawTri(a.x, a.y, b.x, b.y, c.x, c.y, GREEN);
  }
  if (TRI_renderMask & RM_POINT) {
    int halfSize = 2;
    int size = 2 * halfSize;
    Tri_DrawRect(a.x - halfSize, a.y - halfSize, size, size, RED);
    Tri_DrawRect(b.x - halfSize, b.y - halfSize, size, size, RED);
    Tri_DrawRect(c.x - halfSize, c.y - halfSize, size, size, RED);
  }
}
