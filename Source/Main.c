#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Trikonasana/Color.h"
#include "Trikonasana/Display.h"
#include "Trikonasana/Light.h"
#include "Trini/Matrix.h"

#include "Trikonasana/AssetLoader.h"
#include "Trikonasana/Draw.h"
#include "Trikonasana/Render.h"
#include "Trikonasana/Application.h"

#include "Test.c"

Tri_Mesh* cubeMesh;
Tri_Light light;

void start(void) {
    msPerUpdate = 1000. / 60;
    testArray();

    /* cubeMesh = Tri_LoadObj("assets/models/cube/cube.obj"); */
    cubeMesh = Tri_LoadObj("assets/models/beveled_cube/beveled_cube.obj");
    if (!cubeMesh) {
        exit(1);
    }
    cubeMesh->texture = Tri_LoadTexture("assets/textures/w3d_bricks.png");
    
    srand(time(NULL));   // Initialization, should only be called once.
    for (int i = 0; i < arrSize(cubeMesh->vTris); i++) {
        /* int r = rand() % WHITE + 0xFF000000; */
        int r = WHITE;
        arrPush(cubeMesh->triColors, r);
    }

    light.direction = vec3fNorm((Vec3f){1,-1,1});
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
            TRI_ToggleRenderMode(RM_TEXTURE);
        }
        if (TRI_event.key.keysym.sym == 'c') {
            if (TRI_cullMode == CM_NONE) TRI_cullMode = CM_BACK;
            else TRI_cullMode = CM_NONE;
        }
        break;
    }
}

void update(void) {
    float speed = 0.001;
    cubeMesh->rotation.x += speed * 10;
    cubeMesh->rotation.y += speed * 10;
    cubeMesh->rotation.z += speed * 10;

    /* cubeMesh->scale.x += speed; */
    /* cubeMesh->scale.y += speed * 4; */
    /* cubeMesh->scale.z += speed * 4; */

    /* cubeMesh->position.x -= speed * 30; */
    /* cubeMesh->position.y += speed * 30; */
    /* cubeMesh->position.z -= speed * 3; */
    
    /* cubeMesh->position.x = 2; */
    /* cubeMesh->position.y = 1.5; */
    cubeMesh->position.z = 6;
}

void draw(void) {
    Mat4 W = mat4Identity();
    Mat4 Rx = mat4RotateX(cubeMesh->rotation.x);
    Mat4 Ry = mat4RotateY(cubeMesh->rotation.y);
    Mat4 Rz = mat4RotateZ(cubeMesh->rotation.z);
    Mat4 S = mat4Scale(cubeMesh->scale.x, cubeMesh->scale.y, cubeMesh->scale.z);
    Mat4 T = mat4Translate(cubeMesh->position.x, cubeMesh->position.y, cubeMesh->position.z);

    W = mat4MulMat4(S, W);
    W = mat4MulMat4(Rx, W);
    W = mat4MulMat4(Ry, W);
    W = mat4MulMat4(Rz, W);
    W = mat4MulMat4(T, W);
    
    Tri_Face* faces = NULL;
    Vec3f* vertices = cubeMesh->vertices;
    Vec3i* tris = cubeMesh->vTris;
    
    for (int i = 0; i < arrSize(tris); i++) {
        // TRANSFORM to camera space
        int* idx = (int*)(tris + i);
        static Vec4f vs[3];
        for (int j = 0; j < 3; j++) {
            vs[j] = mat4MulVec4(W, vec4FromVec3(vertices[idx[j]]));
        }
        Vec3f worldNorm = Tri_CalcTriNormal(vec3FromVec4(vs[0]), vec3FromVec4(vs[1]), vec3FromVec4(vs[2]));
        if (TRI_cullMode == CM_BACK) {
            if (Tri_CullBackface((Vec3f){0}, vec3FromVec4(vs[0]), worldNorm)) continue;
        }
        for (int j = 0; j < 3; j++) {
            vs[j] = Tri_ProjectPerspective(vs[j]);
        }

        // FACE
        Tri_Face face = {vec3FromVec4(vs[0]), vec3FromVec4(vs[1]), vec3FromVec4(vs[2])};
        face.color = Tri_SetColorBrightness(cubeMesh->triColors[i], Tri_CalcLightIntensity(&light, worldNorm));
        // average face depth used in painter's algorithm
        face.depth =  (face.vertices[0].z + face.vertices[1].z + face.vertices[2].z) / 3.0;
        face.uvs[0] = cubeMesh->uvs[cubeMesh->uvTris[i].x];
        face.uvs[1] = cubeMesh->uvs[cubeMesh->uvTris[i].y];
        face.uvs[2] = cubeMesh->uvs[cubeMesh->uvTris[i].z];

        arrPush(faces, face);
    }

    // Sort ascending (final step in painter's algorithm)
    Tri_SortFaces(faces, 0, arrSize(faces)-1);

    // cam is looking in the positive z direction
    for (int i = arrSize(faces)-1; i >= 0; i--) {
        Tri_Face* face = &faces[i];
        // TRANSFORM to screen space
        Vec3f a = mat3MulVec3(TRI_screenMatrix, face->vertices[0]);
        Vec3f b = mat3MulVec3(TRI_screenMatrix, face->vertices[1]);
        Vec3f c = mat3MulVec3(TRI_screenMatrix, face->vertices[2]);

        // RENDER
        if (TRI_renderMask & RM_TEXTURE) Tri_DrawTriTexture(
            a.x, a.y, b.x, b.y, c.x, c.y,
            face->uvs[0], face->uvs[1], face->uvs[2], cubeMesh->texture);
        else if (TRI_renderMask & RM_SOLID) Tri_DrawTriSolid(a.x, a.y, b.x, b.y, c.x, c.y, face->color);
        if (TRI_renderMask & RM_WIRE) Tri_DrawTri(a.x, a.y, b.x, b.y, c.x, c.y, GREEN);
        if (TRI_renderMask & RM_POINT) {
            int halfSize = 1;
            int size = 2 * halfSize;
            Tri_DrawRect(a.x-halfSize, a.y-halfSize, size, size, RED);
            Tri_DrawRect(b.x-halfSize, b.y-halfSize, size, size, RED);
            Tri_DrawRect(c.x-halfSize, c.y-halfSize, size, size, RED);
        }        
    }
    
    arrDestroy(faces);
}

void stop(void) {
    Tri_DestroyMesh(cubeMesh);
}

// Application
int main(int argc, char *argv[]){
    Tri_RunApp();
    return 0;
}
