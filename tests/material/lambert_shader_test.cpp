#include <cmath>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "material/lambert_shader.h"

namespace {

// A point at the origin whose surface faces up (+Y).
HitInfo hitFacingUp(const Material& material) {
    return HitInfo{Vector(0, 0, 0), Vector(0, 1, 0), &material};
}

}  // namespace

TEST_CASE("Lambert: a surface facing the light gets the full colour") {
    LambertShader shader(Colour(1, 0.5, 0.25));
    Light light(Vector(0, 10, 0), Colour(1, 1, 1));

    Colour colour = shader.shade(hitFacingUp(shader), light);

    REQUIRE(colour.r() == Catch::Approx(1));
    REQUIRE(colour.g() == Catch::Approx(0.5));
    REQUIRE(colour.b() == Catch::Approx(0.25));
}

TEST_CASE("Lambert: a light at 60 degrees gives half the colour (cos 60 = 0.5)") {
    LambertShader shader(Colour(1, 1, 1));
    Light light(Vector(std::sqrt(3.0), 1, 0), Colour(1, 1, 1));

    Colour colour = shader.shade(hitFacingUp(shader), light);

    REQUIRE(colour.r() == Catch::Approx(0.5));
}

TEST_CASE("Lambert: a light behind the surface gives black, not a negative colour") {
    LambertShader shader(Colour(1, 1, 1));
    Light light(Vector(0, -10, 0), Colour(1, 1, 1));

    Colour colour = shader.shade(hitFacingUp(shader), light);

    REQUIRE(colour.r() == 0);
    REQUIRE(colour.g() == 0);
    REQUIRE(colour.b() == 0);
}

TEST_CASE("Lambert: the light colour tints the surface") {
    LambertShader shader(Colour(1, 1, 1));
    Light light(Vector(0, 10, 0), Colour(1, 0, 0));

    Colour colour = shader.shade(hitFacingUp(shader), light);

    REQUIRE(colour.r() == Catch::Approx(1));
    REQUIRE(colour.g() == Catch::Approx(0));
    REQUIRE(colour.b() == Catch::Approx(0));
}
