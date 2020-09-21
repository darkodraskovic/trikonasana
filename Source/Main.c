#include <stdio.h>
#include <stdint.h>

#include "Renderer/Display.h"
#include "Renderer/Draw.h"
#include "Renderer/Consts.h"
#include "Application.h"
#include "Math/Vector.h"

#define N_POINTS 9 * 9 * 9

Vector3 points[N_POINTS];
Vector2 projectedPoints[N_POINTS];

int fovFactor = 512;
Vector3 cameraPosition = {.x = 0, .y = 0, .z = -5};
Vector3 cubeRotation = {.x = 0, .y = 0, .z = 0};

void start(void) {
    float step = 0.25f;
    int cnt = 0;
    for (float x = -1; x <= 1; x += step) {
        for (float y = -1; y <= 1; y += step) {
            for (float z = -1; z <= 1; z += step) {
                Vector3 point = {x, y, z};
                points[cnt++] = point;
            }    
        }        
    }
}

Vector2 projectOrtho(Vector3 point) {
    float x = point.x * fovFactor + windowWidth / 2;
    float y = point.y * fovFactor + windowHeight / 2;
    Vector2 projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

Vector2 projectPerspective(Vector3 point) {
    point.z -= cameraPosition.z;
    float x = point.x / point.z;
    x = x * fovFactor + windowWidth / 2;
    float y = point.y / point.z;
    y = y * fovFactor + windowHeight / 2;
    Vector2 projectedPoint = { .x = x, .y = y };
    return projectedPoint;
}

void update(void) {
    cubeRotation.y += 0.1;
    for (int i = 0; i < N_POINTS; ++i) {
         projectedPoints[i] = projectPerspective(points[i]);
    }
    for (int i = 0; i < N_POINTS; ++i) {
        Vector2 pp =  projectedPoints[i];
        drawRect(pp.x, pp.y, 4, 4, CYAN);
    }
    /* drawGrid(0xFFFF0000, 0, 0, windowWidth, windowHeight, 10); */
    /* drawPixel(windowWidth / 2, windowHeight / 2, 0xFF00FF00); */
    /* drawRect(30, 30, 50, 100, YELLOW); */
}

int main(int argc, char *argv[]){
    runApp();
    return 0;
}
