#include <stdlib.h>

#include "Trini/Vector.h"
#include "Trini/Array.h"

#include "Mesh.h"

Tri_Mesh* Tri_CreateMesh() {
    Tri_Mesh* mesh = malloc(sizeof(Tri_Mesh));
    mesh->vertices = NULL;
    mesh->norms = NULL;
    mesh->tris = NULL;
    mesh->uvs = NULL;
    vec3fSet(&mesh->position, 0, 0, 0);
    vec3fSet(&mesh->rotation, 0, 0, 0);
    vec3fSet(&mesh->scale, 1, 1, 1);
    return mesh;
}

void Tri_DestroyMesh(Tri_Mesh* mesh) {
    arrDestroy(mesh->vertices);
    arrDestroy(mesh->norms);
    arrDestroy(mesh->uvs);
    arrDestroy(mesh->tris);
    free(mesh);
}

void Tri_AddVertex(Tri_Mesh *mesh, Vec3f vertex) {
    arrPush(mesh->vertices, vertex);
}
void Tri_AddVertices(Tri_Mesh *mesh, Vec3f* vertices, int count) {
    arrAppend(mesh->vertices, vertices, count);
}

void Tri_AddTri(Tri_Mesh *mesh, Vec3i tri) {
    arrPush(mesh->tris, tri);
}

void Tri_AddTris(Tri_Mesh *mesh, Vec3i* tris, int count) {
    arrAppend(mesh->tris, tris, count);
}

Vec3f* Tri_RotateMesh(Tri_Mesh* mesh, Vec3f rotation) {
    Vec3f* rotatedVertices = arrCreate(arrSize(mesh->tris)*3, sizeof(Vec3f));
    for (int i = 0; i < arrSize(mesh->tris); i++) {
        Vec3i triIdx = mesh->tris[i];
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
