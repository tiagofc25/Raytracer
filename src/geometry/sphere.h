#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere {
public:
    Sphere(const Vector& center, double radius, std::shared_ptr<Material> material);

    const Vector& center() const;
    double radius() const;
    const Material& material() const;

    // The closest hit in front of the ray origin, or nothing if the ray misses.
    std::optional<HitInfo> intersect(const Ray& ray) const;

private:
    Vector _center;
    double _radius;
    std::shared_ptr<Material> _material;
};
