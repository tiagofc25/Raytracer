#include <memory>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"

namespace {

std::shared_ptr<Material> anyMaterial() {
    return std::make_shared<FlatShader>(Colour(1, 1, 1));
}

}  // namespace

TEST_CASE("A ray that crosses a sphere hits the closest point in front of it") {
    // Example from the board: O = (0, -1), D = (0, 1), C = (0, 9), r = 5 -> t = 5 or 15.
    std::shared_ptr<Material> material = anyMaterial();
    Sphere sphere(Vector(0, 9, 0), 5, material);
    Ray ray(Vector(0, -1, 0), Vector(0, 1, 0));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->point.x() == Catch::Approx(0));
    REQUIRE(hit->point.y() == Catch::Approx(4));
    REQUIRE(hit->point.z() == Catch::Approx(0));
    REQUIRE(hit->normal.x() == Catch::Approx(0));
    REQUIRE(hit->normal.y() == Catch::Approx(-1));
    REQUIRE(hit->normal.z() == Catch::Approx(0));
    REQUIRE(hit->material == material.get());
}

TEST_CASE("A ray that misses a sphere hits nothing") {
    Sphere sphere(Vector(0, 9, 0), 5, anyMaterial());
    Ray ray(Vector(10, -1, 0), Vector(0, 1, 0));

    REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

TEST_CASE("A ray starting inside a sphere hits the exit point, not the point behind it") {
    Sphere sphere(Vector(0, 9, 0), 5, anyMaterial());
    Ray ray(Vector(0, 9, 0), Vector(0, 1, 0));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->point.y() == Catch::Approx(14));
}

TEST_CASE("A sphere behind the ray is not hit") {
    Sphere sphere(Vector(0, 9, 0), 5, anyMaterial());
    Ray ray(Vector(0, 20, 0), Vector(0, 1, 0));

    REQUIRE_FALSE(sphere.intersect(ray).has_value());
}
