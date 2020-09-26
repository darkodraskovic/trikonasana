#include "Mesh.h"
#include "Math/Vector.h"
#include <stdlib.h>

Vec3f cubeVertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 0
    { .x = -1, .y =  1, .z = -1 }, // 1
    { .x =  1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y = -1, .z = -1 }, // 3
    { .x =  1, .y =  1, .z =  1 }, // 4
    { .x =  1, .y = -1, .z =  1 }, // 5
    { .x = -1, .y =  1, .z =  1 }, // 6
    { .x = -1, .y = -1, .z =  1 }  // 7
};                                 

Vec3i cubeTris[N_CUBE_TRIS] = {
    // front
    { .x = 0, .y = 1, .z = 2 },
    { .x = 0, .y = 2, .z = 3 },
    // right
    { .x = 3, .y = 2, .z = 4 },
    { .x = 3, .y = 4, .z = 5 },
    // back
    { .x = 5, .y = 4, .z = 6 },
    { .x = 5, .y = 6, .z = 7 },
    // left
    { .x = 7, .y = 6, .z = 1 },
    { .x = 7, .y = 1, .z = 0 },
    // top
    { .x = 1, .y = 6, .z = 4 },
    { .x = 1, .y = 4, .z = 2 },
    // bottom
    { .x = 5, .y = 7, .z = 0 },
    { .x = 5, .y = 0, .z = 3 }
};

Vec3f* rotateMesh(Mesh* mesh, Vec3f rotation) {
    Vec3f *rotatedVertices = (Vec3f *)malloc(sizeof(Vec3f) * mesh->numTris * 3);
    for (int i = 0; i < mesh->numTris; i++) {
        Vec3i tri = mesh->tris[i];
        Vec3f triVertices[3] = {
            mesh->vertices[tri.x],
            mesh->vertices[tri.y],
            mesh->vertices[tri.z],
        };

        for (int j = 0; j < 3; j++) {
            Vec3f *transformed = &triVertices[j];
            *transformed = rotateVec3fX(transformed, rotation.x);
            *transformed = rotateVec3fY(transformed, rotation.y);
            *transformed = rotateVec3fZ(transformed, rotation.z);
            rotatedVertices[i * 3 + j] = *transformed;
        }
    }
    return rotatedVertices;
}
