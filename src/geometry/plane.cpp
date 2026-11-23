#include "geometry/plane.h"

#include <cmath>
#include <utility>

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material)) {}

const Vector& Plane::point() const { return _point; }
const Vector& Plane::normal() const { return _normal; }
const Material& Plane::material() const { return *_material; }

// P is on the plane if (P - Q) . n = 0. With P = O + tD:
// (O - Q) . n + t (D . n) = 0, so t = (Q - O) . n / (D . n)
std::optional<HitInfo> Plane::intersect(const Ray& ray) const {
    double denominator = ray.direction().dot(_normal);
    if (std::abs(denominator) < 1e-12) {
        return std::nullopt;  // the ray is parallel to the plane
    }

    double t = (_point - ray.origin()).dot(_normal) / denominator;
    if (t < 0.0) {
        return std::nullopt;  // the plane is behind the ray
    }

    return HitInfo{ray.at(t), _normal, _material.get(), t};
}
