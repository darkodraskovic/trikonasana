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

int Tri_CullBackface(Vec3f campPos, Vec3f a, Vec3f b, Vec3f c) {
    Vec3f ab = vec3fSub(b, a);
    Vec3f ac = vec3fSub(c, a);
    Vec3f norm = vec3fCross(ab, ac);
    Vec3f camRay = vec3fSub(campPos, a);
    return vec3fDot(camRay, norm) < 0;
}

Vec2f Tri_ProjectOrtho(Vec3f point) {
    float x = point.x * fovFactor + windowWidth / 2;
    float y = point.y * fovFactor + windowHeight / 2;
    Vec2f projectedPoint = {.x = x, .y = y};
    return projectedPoint;
}

Vec2f Tri_ProjectPerspective(Vec3f point) {
    point.z -= cameraPosition.z;
    float x = point.x / point.z;
    x = x * fovFactor + windowWidth / 2;
    float y = point.y / point.z;
    y = y * fovFactor + windowHeight / 2;
    return (Vec2f){.x = x, .y = y};
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
    /* Vec3f* rotated = Tri_RotateMesh(cubeMesh, cubeMesh->rotation); */
    /* for (int i = 0; i < arrSize(rotated) - 3; i += 3) { */
    /*     Vec3f a = rotated[i]; */
    /*     Vec3f b = rotated[i+1]; */
    /*     Vec3f c = rotated[i+2]; */
        
    /*     if (Tri_CullBackface(cameraPosition, a, b, c)) continue; */
        
    /*     Vec2f pa = Tri_ProjectPerspective(a); */
    /*     Vec2f pb = Tri_ProjectPerspective(b); */
    /*     Vec2f pc = Tri_ProjectPerspective(c); */
    /*     Tri_DrawTri(pa.x, pa.y, pb.x, pb.y, pc.x, pc.y, BLUE); */
    /* } */
    /* arrDestroy(rotated); */
    
    Tri_DrawTri(40, 80, 200, 20, 300, 300, RED);
    Tri_DrawTriSolid(40, 80, 200, 20, 300, 300, BLUE);
}

void stop(void) {
    Tri_DestroyMesh(cubeMesh);
}

// Application
int main(int argc, char *argv[]){
    Tri_RunApp();
    return 0;
}
