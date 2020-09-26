#ifndef MESH_H
#define MESH_H

#include "Math/Vector.h"

typedef struct {
    unsigned numVertices;
    unsigned numTris;
    Vec3f* vertices;
    Vec3i* tris;
} Mesh;

Vec3f* rotateMesh(Mesh* mesh, Vec3f rotation);

#define N_CUBE_VERTICES 8
extern Vec3f cubeVertices[N_CUBE_VERTICES];

#define N_CUBE_TRIS (6 * 2) // 6 cube faces, 2 triangles per face
extern Vec3i cubeTris[N_CUBE_TRIS];

#endif /* MESH_H */
