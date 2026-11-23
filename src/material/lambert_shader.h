#pragma once

#include "material/material.h"

// Matte surface: the more the surface faces the light, the brighter it is.
class LambertShader : public Material {
public:
    explicit LambertShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
