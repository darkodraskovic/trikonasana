#include <stdlib.h>

#include "Trini/Vector.h"
#include "Trini/Array.h"

#include "Mesh.h"

Tri_Mesh* Tri_CreateMesh() {
    Tri_Mesh* mesh = malloc(sizeof(Tri_Mesh));
    mesh->vertices = arrCreate(0, sizeof(float));
    mesh->normals = arrCreate(0, sizeof(float));
    mesh->uvs = arrCreate(0, sizeof(float));
    
    mesh->vTris = arrCreate(0, sizeof(int));
    mesh->nTris = arrCreate(0, sizeof(int));
    mesh->uvTris = arrCreate(0, sizeof(int));
    
    mesh->triColors = arrCreate(0, sizeof(color_t));
    mesh->position = (Vec3f){0,0,0};
    mesh->rotation = (Vec3f){0,0,0};
    mesh->scale = (Vec3f){1,1,1};
    return mesh;
}

void Tri_DestroyMesh(Tri_Mesh* mesh) {
    arrDestroy(mesh->vertices);
    arrDestroy(mesh->normals);
    arrDestroy(mesh->uvs);
    arrDestroy(mesh->vTris);
    free(mesh);
}

Vec3f* Tri_RotateMesh(Tri_Mesh* mesh, Vec3f rotation) {
    Vec3f* rotatedVertices = arrCreate(arrSize(mesh->vTris)*3, sizeof(Vec3f));
    for (int i = 0; i < arrSize(mesh->vTris); i++) {
        Vec3i triIdx = mesh->vTris[i];
        Vec3f triVerts[3] = {
            mesh->vertices[triIdx.x],
            mesh->vertices[triIdx.y],
            mesh->vertices[triIdx.z],
        };

        for (int j = 0; j < 3; j++) {
            Vec3f* transformed = &triVerts[j];
            *transformed = rotateVec3fX(transformed, rotation.x);
            *transformed = rotateVec3fY(transformed, rotation.y);
            *transformed = rotateVec3fZ(transformed, rotation.z);
            arrPush(rotatedVertices, *transformed);
        }
    }
    return rotatedVertices;
}

void Tri_sortFaces(Tri_Face* faces, int first, int last) {
    if (first >= last) return;

    int i, j, pivot;
    Tri_Face temp;
    pivot = first;
    i = first;
    j = last;
    
    while(i < j) {
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
    
    Tri_sortFaces(faces, first, j-1);
    Tri_sortFaces(faces, j+1, last);
}
