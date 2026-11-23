#pragma once

#include <memory>
#include <optional>

#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

// An infinite flat surface, through a point and perpendicular to a normal.
class Plane : public Shape {
public:
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<Material> material);

    const Vector& point() const;
    const Vector& normal() const;
    const Material& material() const;

    std::optional<HitInfo> intersect(const Ray& ray) const override;

private:
    Vector _point;
    Vector _normal;  // stored normalised
    std::shared_ptr<Material> _material;
};
