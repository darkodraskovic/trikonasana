#include "math.h"
#include "Light.h"

float Tri_CalcLightIntensity(Tri_Light* const light, Vec3f normal) {
    Vec3f invLightDir = vec3fInv(light->direction);
    return fmax(0, vec3fDot(invLightDir, normal));
}
