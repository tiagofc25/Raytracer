#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"

// Anything a ray can hit. To add a new kind of object, write a new subclass:
// the rest of the code does not change.
class Shape {
public:
    virtual ~Shape() = default;

    // The closest hit in front of the ray origin, or nothing if the ray misses.
    virtual std::optional<HitInfo> intersect(const Ray& ray) const = 0;
};
