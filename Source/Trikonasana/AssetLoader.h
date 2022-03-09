#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <SDL2/SDL.h>

#include "Trikonasana/Mesh.h"

Tri_Mesh *Tri_LoadObj(char *filePath);
Tri_Texture *Tri_LoadTexture(const char *fileName);

#endif /* ASSETLOADER_H */
