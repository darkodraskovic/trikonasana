#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <time.h>

#include "Application.h"
#include "Trikonasana/AssetLoader.h"
#include "Trikonasana/Color.h"
#include "Trikonasana/Display.h"
#include "Trikonasana/Draw.h"
#include "Trikonasana/Light.h"
#include "Trikonasana/Render.h"
#include "Trini/Array.h"
#include "Trini/Matrix.h"
#include "Trini/Vector.h"

Tri_Mesh* mesh;
Tri_Light light;
Vec3f camPos = {0, 0, 0};

void start(void) {
  msPerUpdate = 1000.f / 60;

  mesh = Tri_LoadObj("assets/models/cube/cube.obj");
  // mesh = Tri_LoadObj("assets/models/beveled_cube/beveled_cube.obj");
  // mesh = Tri_LoadObj("assets/models/f22/f22.obj");
  if (!mesh) {
    exit(1);
  }
  mesh->texture = Tri_LoadTexture("assets/textures/w3d_achtung.png");

  srand(time(NULL));  // Initialization, should only be called once.
  for (int i = 0; i < arrSize(mesh->vTris); i++) {
    /* int r = rand() % WHITE + 0xFF000000; */
    color_t r = WHITE;
    arrPush(mesh->triColors, r);
  }

  light.direction = vec3fNorm((Vec3f){1, -1, 1});

  /* TRI_renderMask = RM_POINT | RM_WIRE | RM_SOLID | RM_TEXTURE; */
  TRI_renderMask = RM_WIRE | RM_SOLID;
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
        if (TRI_cullMode == CM_NONE)
          TRI_cullMode = CM_BACK;
        else
          TRI_cullMode = CM_NONE;
      }
      break;
  }
}

void update(void) {
  float speed = 0.001;

  float rotFactor = 5;
  mesh->rotation.x += speed * rotFactor;
  mesh->rotation.y += speed * rotFactor;
  mesh->rotation.z += speed * rotFactor;

  /* cubeMesh->scale.x += speed; */
  /* cubeMesh->scale.y += speed * 4; */
  /* cubeMesh->scale.z += speed * 4; */

  /* cubeMesh->position.x -= speed * 30; */
  /* cubeMesh->position.y += speed * 30; */
  mesh->position.z = 6;
}

Tri_Face Tri_TransformTri(Tri_Mesh* mesh, int faceIdx, Mat4 worldMat) {
  Vec3f* vertices = mesh->vertices;
  Vec3i* vTris = mesh->vTris;
  Vec2f* uvs = mesh->uvs;
  Vec3i* uvTris = mesh->uvTris;
  color_t* colors = mesh->triColors;

  // get tri vertices
  Vec4f a = vec4FromVec3(vertices[vTris[faceIdx].x]);
  Vec4f b = vec4FromVec3(vertices[vTris[faceIdx].y]);
  Vec4f c = vec4FromVec3(vertices[vTris[faceIdx].z]);

  // transform to world space
  a = mat4MulVec4(worldMat, a);
  b = mat4MulVec4(worldMat, b);
  c = mat4MulVec4(worldMat, c);

  // TODO: transform to view space

  // TODO: transform mesh normals to world/view space instead of face normal recalculation
  Vec3f normal = Tri_CalcTriNormal(vec3FromVec4(a), vec3FromVec4(b), vec3FromVec4(c));

  // cull
  int cull = 0;
  if (TRI_cullMode == CM_BACK) {
    if (Tri_CullBackface(camPos, vec3FromVec4(a), normal)) cull = 1;
  }

  // transform to projection space
  a = Tri_ProjectPerspective(a);
  b = Tri_ProjectPerspective(b);
  c = Tri_ProjectPerspective(c);

  // average face depth used in painter's algorithm
  float averageDepth = (a.z + b.z + c.z) / 3.0;
  Vec3f depth = {a.w, b.w, c.w};

  // transform to screen space
  Vec4f scra = mat4MulVec4(TRI_screenMatrix, (Vec4f){a.x, a.y, a.z, 1.});
  Vec4f scrb = mat4MulVec4(TRI_screenMatrix, (Vec4f){b.x, b.y, b.z, 1.});
  Vec4f scrc = mat4MulVec4(TRI_screenMatrix, (Vec4f){c.x, c.y, c.z, 1.});

  // face to render from transformed mesh face
  Tri_Face face = {
      .vertices = {(Vec4f){scra.x, scra.y, scra.z, depth.x},
                   (Vec4f){scrb.x, scrb.y, scrb.z, depth.y},
                   (Vec4f){scrc.x, scrc.y, scrc.z, depth.z}},
      .color = Tri_SetColorBrightness(colors[faceIdx], Tri_CalcLightIntensity(&light, normal)),
      .depth = averageDepth,
      .cull = cull,
      .normal = normal,
      .texture = mesh->texture};

  face.uvs[0] = uvs[uvTris[faceIdx].x];
  face.uvs[0].y = 1 - face.uvs[0].y;
  face.uvs[1] = uvs[uvTris[faceIdx].y];
  face.uvs[1].y = 1 - face.uvs[1].y;
  face.uvs[2] = uvs[uvTris[faceIdx].z];
  face.uvs[2].y = 1 - face.uvs[2].y;

  return face;
}

void draw(void) {
  Mat4 W = Tri_CalcWorldMatrix(mesh);
  // TODO: calc view matrix

  Tri_Face* faces = NULL;
  for (int i = 0; i < arrSize(mesh->vTris); i++) {
    Tri_Face face = Tri_TransformTri(mesh, i, W);
    arrPush(faces, face);
  }

  // Sort ascending (final step in painter's algorithm)
  Tri_SortFaces(faces, 0, arrSize(faces) - 1);

  // cam is looking in the positive z direction
  for (int i = arrSize(faces) - 1; i >= 0; i--) {
    Tri_RenderFace(&faces[i]);
  }

  arrDestroy(faces);
}

void stop(void) { Tri_DestroyMesh(mesh); }

// Application
#ifdef __MINGW32__
int WinMain(int argc, char* argv[]) {
#elif _WIN64
int wmain(int argc, char* argv[]) {
#elif __linux__
int main(int argc, char* argv[]) {
#endif
  Tri_RunApp();
  return 0;
}
