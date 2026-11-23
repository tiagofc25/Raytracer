#pragma once

#include "math/vector.h"

// A ray: every point on it is origin + t * direction.
class Ray {
public:
    Ray(const Vector& origin, const Vector& direction);

    const Vector& origin() const;
    const Vector& direction() const;

    // The point at distance t along the ray.
    Vector at(double t) const;

private:
    Vector _origin;
    Vector _direction;
};
