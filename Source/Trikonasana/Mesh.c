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
    
    vec3fSet(&mesh->position, 0, 0, 0);
    vec3fSet(&mesh->rotation, 0, 0, 0);
    vec3fSet(&mesh->scale, 1, 1, 1);
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
