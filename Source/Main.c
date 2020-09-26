#include <stdio.h>
#include <stdint.h>

#include "Graphics/Consts.h"
#include "Graphics/Display.h"
#include "Graphics/Draw.h"
#include "Graphics/Triangle.h"
#include "Graphics/Mesh.h"
#include "Application/Application.h"
#include "Math/Vector.h"

int fovFactor = 512;
Vec3 cameraPosition = {.x = 0, .y = 0, .z = -5};

Vec2 projectOrtho(Vec3 point) {
    float x = point.x * fovFactor + windowWidth / 2;
    float y = point.y * fovFactor + windowHeight / 2;
    Vec2 projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

Vec2 projectPerspective(Vec3 point) {
    point.z -= cameraPosition.z;
    float x = point.x / point.z;
    x = x * fovFactor + windowWidth / 2;
    float y = point.y / point.z;
    y = y * fovFactor + windowHeight / 2;
    Vec2 projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////
Vec3 cubeRotation = {.x = 0, .y = 0, .z = 0};
Tri2 trianglesToRender[N_MESH_FACES];
    
void start(void) {

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
    /* drawGrid(0xFFFF0000, 0, 0, windowWidth, windowHeight, 10); */
    /* drawRect(30, 30, 50, 100, YELLOW); */
    
    for (int i = 0; i < N_MESH_FACES; i++) {
        Face face = meshFaces[i];
        Vec3 vertices[3];
        vertices[0] = meshVertices[face.a];
        vertices[1] = meshVertices[face.b];
        vertices[2] = meshVertices[face.c];

        Tri2 projectedTriangle;
        for (int j = 0; j < 3; j++) {
            Vec3 transformedVertex = vertices[j];
            transformedVertex = rotateVec3X(transformedVertex, cubeRotation.x);
            transformedVertex = rotateVec3Y(transformedVertex, cubeRotation.y);
            transformedVertex = rotateVec3Z(transformedVertex, cubeRotation.z);

            projectedTriangle.points[j] = projectPerspective(transformedVertex);
        }

        trianglesToRender[i] = projectedTriangle;
    }

    for (int i = 0; i < N_MESH_FACES; ++i) {
        Tri2 tri = trianglesToRender[i];
        for (int j = 0; j < 3; ++j) {
            Vec2 point = tri.points[j];
            drawRect(point.x, point.y, 4, 4, BLUE);
        }
    }
}

void stop(void) {
    
}

// Application
int main(int argc, char *argv[]){
    runApp();
    return 0;
}
