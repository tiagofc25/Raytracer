#pragma once

#include "colour/colour.h"
#include "math/vector.h"

// A point light: it shines from one position in every direction.
class Light {
public:
    Light(const Vector& position, const Colour& colour);

    const Vector& position() const;
    const Colour& colour() const;

private:
    Vector _position;
    Colour _colour;
};
