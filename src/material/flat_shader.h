#pragma once

#include "material/material.h"

// Always the same colour, whatever the light.
class FlatShader : public Material {
public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
