#ifndef MESH_H
#define MESH_H

#include "Trini/Vector.h"
#include "Trikonasana/Color.h"

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
    
    color_t* triColors; // face colors
    Tri_Texture* texture;
} Tri_Mesh;

// Tri_Face is used to render face and is populated from (transformed) Tri_Mesh data
typedef struct {
    Vec3f vertices[3];
    Vec2f uvs[3];
    color_t color;
    float depth;
} Tri_Face;

Tri_Mesh *Tri_CreateMesh();
void Tri_DestroyMesh(Tri_Mesh *mesh);
Vec3f Tri_CalcTriNormal(Vec3f a, Vec3f b, Vec3f c);
void Tri_SortFaces(Tri_Face* faces, int first,int last);

#endif /* MESH_H */
