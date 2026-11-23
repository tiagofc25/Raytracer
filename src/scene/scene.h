#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "light/light.h"

// Everything there is to see: the objects, the light, and the colour of the sky.
class Scene {
public:
    Scene(const Light& light, const Colour& background);

    void add(std::shared_ptr<Shape> shape);

    const Light& light() const;
    const Colour& background() const;

    // The hit closest to the ray origin among all the objects, or nothing.
    std::optional<HitInfo> closestHit(const Ray& ray) const;

    // True if an object stands between the hit point and the light.
    bool isInShadow(const HitInfo& hit) const;

private:
    Light _light;
    Colour _background;
    std::vector<std::shared_ptr<Shape>> _shapes;
};
