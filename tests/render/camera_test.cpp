#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "render/camera.h"

namespace {

void requireDirection(const Ray& ray, double x, double y, double z) {
    REQUIRE(ray.direction().x() == Catch::Approx(x));
    REQUIRE(ray.direction().y() == Catch::Approx(y));
    REQUIRE(ray.direction().z() == Catch::Approx(z));
}

}  // namespace

TEST_CASE("rayThroughPixel: screen width 5, image of 5 columns and 3 rows") {
    Camera camera(Vector(0, 0, 0));

    SECTION("pixel (2, 1), in the center, has direction (0, 0, 1)") {
        requireDirection(camera.rayThroughPixel(2, 1, 5, 3, 5), 0, 0, 1);
    }

    SECTION("pixel (4, 0), top right, has direction (2, 1, 1)") {
        requireDirection(camera.rayThroughPixel(4, 0, 5, 3, 5), 2, 1, 1);
    }

    SECTION("pixel (0, 2), bottom left, has direction (-2, -1, 1)") {
        requireDirection(camera.rayThroughPixel(0, 2, 5, 3, 5), -2, -1, 1);
    }

    SECTION("every ray starts at the camera position") {
        Ray ray = camera.rayThroughPixel(4, 0, 5, 3, 5);
        REQUIRE(ray.origin().x() == 0);
        REQUIRE(ray.origin().y() == 0);
        REQUIRE(ray.origin().z() == 0);
    }
}

TEST_CASE("rayThroughPixel: screen width 2, image of 512 columns and 256 rows") {
    // Pixel size = 2 / 512 = 1/256, so the screen is 1 unit high.
    Camera camera(Vector(0, 0, 0));
    double halfPixel = 0.5 / 256.0;

    SECTION("pixel (0, 0), top left") {
        requireDirection(camera.rayThroughPixel(0, 0, 512, 256, 2), -1 + halfPixel, 0.5 - halfPixel, 1);
    }

    SECTION("pixel (511, 255), bottom right") {
        requireDirection(camera.rayThroughPixel(511, 255, 512, 256, 2), 1 - halfPixel, -0.5 + halfPixel, 1);
    }

    SECTION("pixel (256, 128), just below and right of the center") {
        requireDirection(camera.rayThroughPixel(256, 128, 512, 256, 2), halfPixel, -halfPixel, 1);
    }
}
