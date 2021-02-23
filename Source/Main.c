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
        
        if (Tri_CullBackface(camPos, a, b, c)) continue;
        
        Vec2f pa = Tri_ProjectPerspective(camPos, a);
        Vec2f pb = Tri_ProjectPerspective(camPos, b);
        Vec2f pc = Tri_ProjectPerspective(camPos, c);
        Tri_DrawTriSolid(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, BLUE);
        Tri_DrawTri(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, GREEN);
    }
    arrDestroy(rotated);
    
    /* Tri_DrawTri(40, 80, 200, 20, 300, 300, RED); */
    /* Tri_DrawTriSolid(40, 80, 200, 20, 300, 300, BLUE); */
}

void stop(void) {
    Tri_DestroyMesh(cubeMesh);
}

// Application
int main(int argc, char *argv[]){
    Tri_RunApp();
    return 0;
}
