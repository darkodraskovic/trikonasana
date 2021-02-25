#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdio.h>

#include "Trikonasana/AssetLoader.h"
#include "Trikonasana/Consts.h"
#include "Trikonasana/Draw.h"
#include "Trikonasana/Render.h"
#include "Trikonasana/Application.h"

#include "Test.c"
#include "Cube.h"

Vec3f camPos = {.x = 0, .y = 0, .z = -7};
Tri_Mesh* cubeMesh;

void start(void) {
    msPerUpdate = 1000. / 60;
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

    switch (TRI_event.type) {
    case SDL_KEYDOWN:
        if (TRI_event.key.keysym.sym == SDLK_1) {
            TRI_ToggleRenderMode(RM_POINT);
        }
        if (TRI_event.key.keysym.sym == SDLK_2) {
            TRI_ToggleRenderMode(RM_WIRE);
        }
        if (TRI_event.key.keysym.sym == SDLK_3) {
            TRI_ToggleRenderMode(RM_SOLID);
        }
        if (TRI_event.key.keysym.sym == SDLK_4) {
            if (TRI_cullMode == CM_NONE) TRI_cullMode = CM_BACK;
            else TRI_cullMode = CM_NONE;
        }
        break;
    }
}

void update(void) {
    float rotSpeed = 0.01;
    cubeMesh->rotation.x += rotSpeed;
    cubeMesh->rotation.y += rotSpeed;
    cubeMesh->rotation.z += rotSpeed;
}

void draw(void) {
    Vec3f* rotated = Tri_RotateMesh(cubeMesh, cubeMesh->rotation);
    for (int i = 0; i < arrSize(rotated) - 3; i += 3) {
        Vec3f a = rotated[i];
        Vec3f b = rotated[i+1];
        Vec3f c = rotated[i+2];

        if (TRI_cullMode == CM_BACK) {
            if (Tri_CullBackface(camPos, a, b, c)) continue;            
        }
        
        Vec2f pa = Tri_ProjectPerspective(camPos, a);
        Vec2f pb = Tri_ProjectPerspective(camPos, b);
        Vec2f pc = Tri_ProjectPerspective(camPos, c);

        if (TRI_renderMask & RM_SOLID) Tri_DrawTriSolid(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, BLUE);
        if (TRI_renderMask & RM_WIRE) Tri_DrawTri(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, GREEN);
        if (TRI_renderMask & RM_POINT) {
            /* Tri_DrawPixel(pa.x, pa.y, RED); */
            /* Tri_DrawPixel(pb.x, pb.y, RED); */
            /* Tri_DrawPixel(pc.x, pc.y, RED); */
            int halfSize = 1;
            int size = 2 * halfSize;
            Tri_DrawRect(pa.x-halfSize, pa.y-halfSize, size, size, RED);
            Tri_DrawRect(pb.x-halfSize, pb.y-halfSize, size, size, RED);
            Tri_DrawRect(pc.x-halfSize, pc.y-halfSize, size, size, RED);
        }
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
