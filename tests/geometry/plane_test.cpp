#include <memory>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "geometry/plane.h"
#include "geometry/ray.h"
#include "material/flat_shader.h"

namespace {

std::shared_ptr<Material> anyMaterial() {
    return std::make_shared<FlatShader>(Colour(1, 1, 1));
}

}  // namespace

TEST_CASE("A ray hits a plane where (P - Q) . n = 0") {
    // Example from the board: O = (-8, 0), D = (4, 3), Q = (8, 0), n = (3, 4) -> t = 2, P = (0, 6).
    std::shared_ptr<Material> material = anyMaterial();
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), material);
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    std::optional<HitInfo> hit = plane.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == Catch::Approx(2));
    REQUIRE(hit->point.x() == Catch::Approx(0));
    REQUIRE(hit->point.y() == Catch::Approx(6));
    REQUIRE(hit->normal.x() == Catch::Approx(3.0 / 5.0));
    REQUIRE(hit->normal.y() == Catch::Approx(4.0 / 5.0));
    REQUIRE(hit->material == material.get());
}

TEST_CASE("A ray parallel to a plane never hits it") {
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 0), anyMaterial());
    Ray ray(Vector(0, 1, 0), Vector(1, 0, 0));

    REQUIRE_FALSE(plane.intersect(ray).has_value());
}

TEST_CASE("A plane behind the ray is not hit") {
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 0), anyMaterial());
    Ray ray(Vector(0, 1, 0), Vector(0, 1, 0));

    REQUIRE_FALSE(plane.intersect(ray).has_value());
}
