#include <stdio.h>
#include <stdint.h>

#include "Graphics/Consts.h"
#include "Graphics/Display.h"
#include "Graphics/Draw.h"
#include "Application/Application.h"
#include "Math/Vector.h"

#define N_POINTS 9 * 9 * 9

Vec3 points[N_POINTS];
Vec2 projectedPoints[N_POINTS];

int fovFactor = 512;
Vec3 cameraPosition = {.x = 0, .y = 0, .z = -5};
Vec3 cubeRotation = {.x = 0, .y = 0, .z = 0};

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

void start(void) {
    float step = 0.25f;
    int cnt = 0;
    for (float x = -1; x <= 1; x += step) {
        for (float y = -1; y <= 1; y += step) {
            for (float z = -1; z <= 1; z += step) {
                Vec3 point = {x, y, z};
                points[cnt++] = point;
            }    
        }        
    }
}

void input() {
    
}

void update(void) {
    float rotSpeed = 0.01;
    cubeRotation.x += rotSpeed;
    cubeRotation.y += rotSpeed;
    cubeRotation.z += rotSpeed;
    for (int i = 0; i < N_POINTS; ++i) {
        Vec3 point = points[i];
        point = rotateVec3X(point, cubeRotation.x);
        point = rotateVec3Y(point, cubeRotation.y);
        point = rotateVec3Z(point, cubeRotation.z);
        
        projectedPoints[i] = projectPerspective(point);
    }
    /* drawGrid(0xFFFF0000, 0, 0, windowWidth, windowHeight, 10); */
    /* drawPixel(windowWidth / 2, windowHeight / 2, 0xFF00FF00); */
    /* drawRect(30, 30, 50, 100, YELLOW); */
}

void draw(void) {
    for (int i = 0; i < N_POINTS; ++i) {
        Vec2 pp =  projectedPoints[i];
        drawRect(pp.x, pp.y, 4, 4, CYAN);
    }    
}

void stop(void) {
    
}

// Application
int main(int argc, char *argv[]){
    runApp();
    return 0;
}
