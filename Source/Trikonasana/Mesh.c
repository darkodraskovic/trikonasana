#include <stdlib.h>
#include "Mesh.h"
#include "Trini/Array.h"
#include "Trini/Vector.h"

Vec3f* Tri_RotateMesh(Tri_Mesh* mesh, Vec3f rotation) {
    Vec3f* rotatedVertices = arrCreate(arrLen(mesh->vertices), sizeof(Vec3f));
    for (int i = 0; i < arrLen(mesh->tris); i++) {
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
            arrPush(rotatedVertices, *transformed);
        }
    }
    return rotatedVertices;
}
