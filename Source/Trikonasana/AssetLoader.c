#include "AssetLoader.h"

#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Display.h"
#include "Trikonasana/Color.h"
#include "Trini/Array.h"

#define LINE_LEN 256

char line[LINE_LEN];

// List of geometric vertices
char* vFmt = "v %f %f %f";
int vCount = 3;

// List of texture coordinates
char* vtFmt = "vt %f %f";
int vtCount = 2;

// List of vertex normals
char* vnFmt = "vn %f %f %f";
int vnCount = 3;

// Face element: vertex_index/texture_index/normal_index
char* fFmt = "f %i/%i/%i %i/%i/%i %i/%i/%i";
int fCount = 9;

Tri_Mesh* Tri_LoadObj(char* filePath) {
  FILE* file;
  file = fopen(filePath, "r");
  if (!file) {
    fprintf(stderr, "Error opening obj file.\n");
    return NULL;
  }

  Tri_Mesh* mesh = Tri_CreateMesh();

  while (fgets(line, LINE_LEN, file)) {
    if (!strncmp(line, vFmt, 2)) {
      Vec3f vert;
      if (sscanf(line, vFmt, &vert.x, &vert.y, &vert.z) < vCount) {
        fprintf(stderr, "Error reading vertex from obj file.\n");
        return NULL;
      };
      arrPush(mesh->vertices, vert);
    } else if (!strncmp(line, vtFmt, 3)) {
      Vec2f uv;
      if (sscanf(line, vtFmt, &uv.x, &uv.y) < vtCount) {
        fprintf(stderr, "Error reading tex coords from obj file.\n");
        return NULL;
      };
      arrPush(mesh->uvs, uv);
    } else if (!strncmp(line, vnFmt, 3)) {
      Vec3f norm;
      if (sscanf(line, vnFmt, &norm.x, &norm.y, &norm.z) < vnCount) {
        fprintf(stderr, "Error reading normals from obj file.\n");
        return NULL;
      };
      arrPush(mesh->normals, norm);
    } else if (!strncmp(line, fFmt, 2)) {
      Vec3i vTri, uvTri, nTri;
      if (sscanf(line, fFmt, &vTri.x, &uvTri.x, &nTri.x, &vTri.y, &uvTri.y, &nTri.y, &vTri.z,
                 &uvTri.z, &nTri.z) < fCount) {
        fprintf(stderr, "Error reading tri from obj file.\n");
        return NULL;
      };

      // each index starts at 1
      vTri.x--;
      vTri.y--;
      vTri.z--;
      uvTri.x--;
      uvTri.y--;
      uvTri.z--;
      nTri.x--;
      nTri.y--;
      nTri.z--;

      arrPush(mesh->uvTris, uvTri);
      arrPush(mesh->vTris, vTri);
      arrPush(mesh->nTris, nTri);
    }
  }

  fclose(file);

  return mesh;
}

Tri_Texture* Tri_LoadTexture(const char* fileName) {
  SDL_Surface* surface = IMG_Load(fileName);

  Tri_Texture* texture = calloc(1, sizeof(Tri_Texture));

  texture->width = surface->w;
  texture->height = surface->h;

  size_t size = surface->w * surface->h * sizeof(uint32_t);
  texture->data = malloc(size);
  memcpy(texture->data, (uint32_t*)surface->pixels, size);

  SDL_FreeSurface(surface);
  return texture;
}
