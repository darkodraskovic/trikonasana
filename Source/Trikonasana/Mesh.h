#ifndef MESH_H
#define MESH_H

#include "Trikonasana/Color.h"
#include "Trini/Matrix.h"
#include "Trini/Vector.h"

typedef struct {
  Vec3f position;
  Vec3f rotation;
  Vec3f scale;

  Vec3f* vertices;
  Vec3f* normals;
  Vec2f* uvs;

  Vec3i* vTris;
  Vec3i* nTris;
  Vec3i* uvTris;

  color_t* triColors;  // face colors
  Tri_Texture* texture;
} Tri_Mesh;

Tri_Mesh* Tri_CreateMesh();
void Tri_DestroyMesh(Tri_Mesh* mesh);
Vec3f Tri_CalcTriNormal(Vec3f a, Vec3f b, Vec3f c);
Mat4 Tri_CalcWorldMatrix(Tri_Mesh* mesh);

#endif /* MESH_H */
