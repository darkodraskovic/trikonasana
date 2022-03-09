#ifndef LIGHT_H
#define LIGHT_H

#include "Trikonasana/Mesh.h"
#include "Trini/Vector.h"

typedef struct {
  Vec3f direction;
} Tri_Light;

float Tri_CalcLightIntensity(Tri_Light* const light, Vec3f normal);

#endif /* LIGHT_H */
