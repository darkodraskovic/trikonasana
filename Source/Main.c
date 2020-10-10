#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "Graphics/Consts.h"
#include "Graphics/Display.h"
#include "Graphics/Draw.h"
#include "Graphics/Mesh.h"
#include "Application/Application.h"
#include "Math/Vector.h"

int fovFactor = 512;
Vec3f cameraPosition = {.x = 0, .y = 0, .z = -5};

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
    Vec2f projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////
Vec3f cubeRotation = {.x = 0, .y = 0, .z = 0};
Mesh cubeMesh = {
    .numVertices = N_CUBE_VERTICES,
    .numTris = N_CUBE_TRIS,
    .vertices = cubeVertices,
    .tris = cubeTris,
};
    
void start(void) {
    msPerUpdate = 1000 / 30;
}

void input() {
    
}

void update(void) {
    float rotSpeed = 0.01;
    cubeRotation.x += rotSpeed;
    cubeRotation.y += rotSpeed;
    cubeRotation.z += rotSpeed;
}

void draw(void) {
    /* drawGrid(RED, 0, 0, windowWidth, windowHeight, 10); */
    /* drawRect(30, 30, 50, 100, YELLOW); */

    Vec3f* rotated = rotateMesh(&cubeMesh, cubeRotation);
    for (int i = 0; i < cubeMesh.numTris * 3 - 3; i += 3) {
      Vec2f a = projectPerspective(rotated[i]);
      Vec2f b = projectPerspective(rotated[i + 1]);
      Vec2f c = projectPerspective(rotated[i + 2]);
      drawTri(a.x, a.y, b.x, b.y, c.x, c.y, BLUE);
    }
    free(rotated);
}

void stop(void) {
    
}

// Application
int main(int argc, char *argv[]){
    runApp();
    return 0;
}
