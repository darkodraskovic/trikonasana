#ifndef MESH_H
#define MESH_H

#include "Math/Vector.h"
#include "Triangle.h"

#define N_MESH_VERTICES 8
extern Vec3 meshVertices[N_MESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 cube faces, 2 triangles per face
extern Face meshFaces[N_MESH_FACES];

// typedef struct {
//     Vec3* vertices;
//     Face* faces;
// } Mesh;

#endif /* MESH_H */
