#ifndef MESH_H
#define MESH_H

#include "Trini/Array.h"
#include "Trini/Vector.h"

typedef struct {
    Vec3f* vertices;
    Vec3i* tris;
} Tri_Mesh;


Vec3f *Tri_RotateMesh(Tri_Mesh *mesh, Vec3f rotation);

#endif /* MESH_H */
