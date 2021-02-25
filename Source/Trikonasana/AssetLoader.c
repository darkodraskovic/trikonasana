#include <stdio.h>
#include <string.h>

#include "AssetLoader.h"

#define LINE_LEN 256

char line[LINE_LEN];
char* vFmt = "v %f %f %f";
int vCount = 3;
char* fFmt = "f %i/%i/%i %i/%i/%i %i/%i/%i";
int fCount = 9;

Tri_Mesh* Tri_LoadObj(char* filePath) {
    FILE* file;
    file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening obj file.\n");
        return NULL;
    }

    Tri_Mesh* mesh = Tri_CreateMesh();
    while (fgets(line, LINE_LEN, file)) {
        if (!strncmp(line, vFmt, 2)) {
            Vec3f vert;
            if (sscanf(line, vFmt, &vert.x, &vert.y, &vert.z) < vCount) {
                fprintf(stderr, "Error reading vertex from obj file.\n");
                return NULL;
            };
            Tri_AddVertex(mesh, vert);
        } else if (!strncmp(line, fFmt, 2)) {
            Vec3i tri, uvs, norms;
            if (sscanf(line, fFmt, &tri.x, &uvs.x, &norms.x, &tri.y, &uvs.y,
                       &norms.y, &tri.z, &uvs.z, &norms.z) < fCount) {
                fprintf(stderr, "Error reading tri from obj file.\n");
                return NULL;
            };
            tri.x--; tri.y--; tri.z--;
            Tri_AddTri(mesh, tri);
        }
    }

    fclose(file);

    return mesh;
}
