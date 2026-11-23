#include "scene/scene.h"

#include <utility>

namespace {

// Start shadow rays a tiny bit above the surface. Without this, rounding errors
// make a surface shadow itself, which gives black dots ("shadow acne").
const double SURFACE_OFFSET = 1e-6;

}  // namespace

Scene::Scene(const Light& light, const Colour& background)
    : _light(light), _background(background) {}

void Scene::add(std::shared_ptr<Shape> shape) {
    _shapes.push_back(std::move(shape));
}

const Light& Scene::light() const { return _light; }
const Colour& Scene::background() const { return _background; }

std::optional<HitInfo> Scene::closestHit(const Ray& ray) const {
    std::optional<HitInfo> closest;
    for (const std::shared_ptr<Shape>& shape : _shapes) {
        std::optional<HitInfo> hit = shape->intersect(ray);
        if (hit && (!closest || hit->t < closest->t)) {
            closest = hit;
        }
    }
    return closest;
}

bool Scene::isInShadow(const HitInfo& hit) const {
    Vector origin = hit.point + hit.normal * SURFACE_OFFSET;
    // Not normalised on purpose: t = 1 is exactly the light, so anything
    // hit with t < 1 is between the point and the light.
    Ray shadowRay(origin, _light.position() - origin);

    std::optional<HitInfo> blocker = closestHit(shadowRay);
    return blocker && blocker->t < 1.0;
}
