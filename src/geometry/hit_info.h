#pragma once

#include "math/vector.h"

class Material;

// What we know about the place where a ray hits an object.
struct HitInfo {
    Vector point;
    Vector normal;              // normalised, pointing out of the surface
    const Material* material;   // owned by the object that was hit
};
