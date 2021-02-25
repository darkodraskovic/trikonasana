#ifndef MESH_H
#define MESH_H

#include "Trini/Vector.h"

typedef struct {
    Vec3f* vertices;
    Vec3f* norms;
    Vec2f* uvs;
    
    Vec3i* tris;
    
    Vec3f position;
    Vec3f rotation;
    Vec3f scale;
} Tri_Mesh;


Tri_Mesh *Tri_CreateMesh();
void Tri_DestroyMesh(Tri_Mesh* mesh);
void Tri_AddVertex(Tri_Mesh* mesh, Vec3f vertex);
void Tri_AddVertices(Tri_Mesh* mesh, Vec3f* vertices, int count);
void Tri_AddTri(Tri_Mesh* mesh, Vec3i tri);
void Tri_AddTris(Tri_Mesh* mesh, Vec3i* tris, int count);

Vec3f* Tri_RotateMesh(Tri_Mesh* mesh, Vec3f rotation);

#endif /* MESH_H */
