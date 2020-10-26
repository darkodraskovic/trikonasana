#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Trikonasana/AssetLoader.h"
#include "Trikonasana/Consts.h"
#include "Trikonasana/Display.h"
#include "Trikonasana/Draw.h"
#include "Trikonasana/Mesh.h"
#include "Trikonasana/Application.h"
#include "Trini/Vector.h"
#include "Trini/Array.h"

#include "Test.c"
#include "Cube.h"

int fovFactor = 512;
Vec3f cameraPosition = {.x = 0, .y = 0, .z = -7};

Vec2f projectOrtho(Vec3f point) {
    float x = point.x * fovFactor + windowWidth / 2;
    float y = point.y * fovFactor + windowHeight / 2;
    Vec2f projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

Vec2f projectPerspective(Vec3f point) {
    point.z -= cameraPosition.z;
    float x = point.x / point.z;
    x = x * fovFactor + windowWidth / 2;
    float y = point.y / point.z;
    y = y * fovFactor + windowHeight / 2;
    return (Vec2f){ .x = x, .y = y };
}

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////
/* Vec3f cubeRotation = {.x = 0, .y = 0, .z = 0}; */
Tri_Mesh* cubeMesh;


void start(void) {
    msPerUpdate = 1000 / 30;
    testArray();

    /* Tri_AddVertices(cubeMesh, cubeVertices, N_CUBE_VERTICES); */
    /* Tri_AddTris(cubeMesh, cubeTris, N_CUBE_TRIS); */

    /* Tri_Mesh* mesh = Tri_CreateMesh(); */

    cubeMesh = Tri_LoadObj("assets/cube.obj");
    if (!cubeMesh) {
        exit(1);
    }
}

void input() {
    
}

void update(void) {
    float rotSpeed = 0.01;
    cubeMesh->rotation.x += rotSpeed;
    cubeMesh->rotation.y += rotSpeed;
    cubeMesh->rotation.z += rotSpeed;
}

void draw(void) {
    Vec3f* rotated = Tri_RotateMesh(cubeMesh, cubeMesh->rotation);
    for (int i = 0; i < arrLen(rotated) - 3; i += 3) {
        Vec2f a = projectPerspective(rotated[i]);
        Vec2f b = projectPerspective(rotated[i + 1]);
        Vec2f c = projectPerspective(rotated[i + 2]);
        Tri_DrawTri(a.x, a.y, b.x, b.y, c.x, c.y, BLUE);
    }
    arrDestroy(rotated);
}

void stop(void) {
    Tri_DestroyMesh(cubeMesh);
}

// Application
int main(int argc, char *argv[]){
    Tri_RunApp();
    return 0;
}
