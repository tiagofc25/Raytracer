#pragma once

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "light/light.h"

// Strategy: one way of computing the colour of a surface at a hit point.
class Material {
public:
    virtual ~Material() = default;

    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
