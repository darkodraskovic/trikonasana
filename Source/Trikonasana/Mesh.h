#ifndef MESH_H
#define MESH_H

#include "Trikonasana/Typedef.h"
#include "Trini/Vector.h"

typedef struct {
    Vec3f* vertices;
    Vec3f* normals;
    Vec2f* uvs;
    
    Vec3i* vTris;
    Vec3i* nTris;
    Vec3i* uvTris;
    
    color_t* triColors; // face colors
    
    Vec3f position;
    Vec3f rotation;
    Vec3f scale;
} Tri_Mesh;

typedef struct {
    Vec3f vertices[3];
    color_t color;
    float depth;
} Tri_Face;

Tri_Mesh *Tri_CreateMesh();
void Tri_DestroyMesh(Tri_Mesh *mesh);

Vec3f *Tri_RotateMesh(Tri_Mesh *mesh, Vec3f rotation);
void Tri_sortFaces(Tri_Face* faces, int first,int last);

#endif /* MESH_H */
