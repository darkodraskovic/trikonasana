#include "Mesh.h"

#include <stdlib.h>

#include "Trini/Array.h"

Tri_Mesh* Tri_CreateMesh() {
  Tri_Mesh* mesh = malloc(sizeof(Tri_Mesh));
  mesh->vertices = arrCreate(0, sizeof(float));
  mesh->normals = arrCreate(0, sizeof(float));
  mesh->uvs = arrCreate(0, sizeof(float));

  mesh->vTris = arrCreate(0, sizeof(int));
  mesh->nTris = arrCreate(0, sizeof(int));
  mesh->uvTris = arrCreate(0, sizeof(int));

  mesh->triColors = arrCreate(0, sizeof(color_t));
  mesh->position = (Vec3f){0, 0, 0};
  mesh->rotation = (Vec3f){0, 0, 0};
  mesh->scale = (Vec3f){1, 1, 1};
  return mesh;
}

void Tri_DestroyMesh(Tri_Mesh* mesh) {
  arrDestroy(mesh->vertices);
  arrDestroy(mesh->normals);
  arrDestroy(mesh->uvs);
  arrDestroy(mesh->vTris);
  free(mesh);
}

Vec3f Tri_CalcTriNormal(Vec3f a, Vec3f b, Vec3f c) {
  Vec3f ab = vec3fSub(b, a);
  Vec3f ac = vec3fSub(c, a);
  return vec3fNorm(vec3fCross(ab, ac));
}

Mat4 Tri_CalcWorldMatrix(Tri_Mesh* mesh) {
  Vec3f rotation = mesh->rotation;
  Vec3f scale = mesh->scale;
  Vec3f position = mesh->position;

  Mat4 Rx = mat4RotateX(rotation.x);
  Mat4 Ry = mat4RotateY(rotation.y);
  Mat4 Rz = mat4RotateZ(rotation.z);
  Mat4 S = mat4Scale(scale.x, scale.y, scale.z);
  Mat4 T = mat4Translate(position.x, position.y, position.z);

  Mat4 W = mat4Identity();
  W = mat4MulMat4(S, W);
  W = mat4MulMat4(Rx, W);
  W = mat4MulMat4(Ry, W);
  W = mat4MulMat4(Rz, W);
  W = mat4MulMat4(T, W);

  return W;
}
