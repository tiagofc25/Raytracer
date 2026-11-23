#include "geometry/sphere.h"

#include <cmath>
#include <utility>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

const Vector& Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
const Material& Sphere::material() const { return *_material; }

// Solve a*t^2 + b*t + c = 0 with L = origin - center:
// a = D.D, b = 2 D.L, c = L.L - r^2
std::optional<HitInfo> Sphere::intersect(const Ray& ray) const {
    Vector l = ray.origin() - _center;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * ray.direction().dot(l);
    double c = l.dot(l) - _radius * _radius;

    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double root = std::sqrt(discriminant);
    double tNear = (-b - root) / (2.0 * a);
    double tFar = (-b + root) / (2.0 * a);

    // Ignore negative t (behind the ray), and keep the lowest positive one.
    double t;
    if (tNear >= 0.0) {
        t = tNear;
    } else if (tFar >= 0.0) {
        t = tFar;
    } else {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();
    return HitInfo{point, normal, _material.get(), t};
}
