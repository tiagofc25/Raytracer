#include <memory>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "scene/scene.h"

namespace {

std::shared_ptr<Material> anyMaterial() {
    return std::make_shared<FlatShader>(Colour(1, 1, 1));
}

Light sunAbove() {
    return Light(Vector(0, 100, 0), Colour(1, 1, 1));
}

}  // namespace

TEST_CASE("A scene returns the closest of the objects hit by a ray") {
    Scene scene(sunAbove(), Colour(0, 0, 0));
    scene.add(std::make_shared<Sphere>(Vector(0, 0, 20), 1, anyMaterial()));
    scene.add(std::make_shared<Sphere>(Vector(0, 0, 10), 1, anyMaterial()));

    std::optional<HitInfo> hit = scene.closestHit(Ray(Vector(0, 0, 0), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE(hit->point.z() == Catch::Approx(9));
}

TEST_CASE("A scene returns nothing when the ray hits no object") {
    Scene scene(sunAbove(), Colour(0, 0, 0));
    scene.add(std::make_shared<Sphere>(Vector(0, 0, 10), 1, anyMaterial()));

    REQUIRE_FALSE(scene.closestHit(Ray(Vector(0, 0, 0), Vector(0, 1, 0))).has_value());
}

TEST_CASE("A point on the ground under a sphere is in its shadow") {
    Scene scene(sunAbove(), Colour(0, 0, 0));
    scene.add(std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0), anyMaterial()));
    scene.add(std::make_shared<Sphere>(Vector(0, 2, 0), 1, anyMaterial()));

    REQUIRE(scene.isInShadow(HitInfo{Vector(0, 0, 0), Vector(0, 1, 0), nullptr, 0}));
}

TEST_CASE("A point on the ground away from the sphere is lit") {
    Scene scene(sunAbove(), Colour(0, 0, 0));
    scene.add(std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0), anyMaterial()));
    scene.add(std::make_shared<Sphere>(Vector(0, 2, 0), 1, anyMaterial()));

    REQUIRE_FALSE(scene.isInShadow(HitInfo{Vector(10, 0, 0), Vector(0, 1, 0), nullptr, 0}));
}

TEST_CASE("An object behind the light does not cast a shadow") {
    Scene scene(Light(Vector(0, 5, 0), Colour(1, 1, 1)), Colour(0, 0, 0));
    scene.add(std::make_shared<Sphere>(Vector(0, 10, 0), 1, anyMaterial()));

    REQUIRE_FALSE(scene.isInShadow(HitInfo{Vector(0, 0, 0), Vector(0, 1, 0), nullptr, 0}));
}
