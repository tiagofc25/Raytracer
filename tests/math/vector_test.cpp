#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "math/vector.h"

TEST_CASE("Adding two vectors adds each component") {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);

    Vector v3 = v1 + v2;

    REQUIRE(v3.x() == 5);
    REQUIRE(v3.y() == 7);
    REQUIRE(v3.z() == 9);
}

TEST_CASE("Subtracting two vectors subtracts each component") {
    Vector v1(-1, 4, 0);
    Vector v2(-5, 2, 1);

    Vector v3 = v1 - v2;

    REQUIRE(v3.x() == 4);
    REQUIRE(v3.y() == 2);
    REQUIRE(v3.z() == -1);
}

TEST_CASE("Multiplying a number by a vector (2 * v) scales each component") {
    Vector v(1, -2, 3);

    Vector result = 2 * v;

    REQUIRE(result.x() == 2);
    REQUIRE(result.y() == -4);
    REQUIRE(result.z() == 6);
}

TEST_CASE("Multiplying a vector by a number (v * 2) scales each component") {
    Vector v(1, -2, 3);

    Vector result = v * 2;

    REQUIRE(result.x() == 2);
    REQUIRE(result.y() == -4);
    REQUIRE(result.z() == 6);
}

TEST_CASE("Normalising a vector keeps its direction and gives it length 1") {
    Vector v(3, 4, 0);

    Vector n = v.normalised();

    REQUIRE(n.x() == Catch::Approx(3.0 / 5.0));
    REQUIRE(n.y() == Catch::Approx(4.0 / 5.0));
    REQUIRE(n.z() == Catch::Approx(0.0));
    REQUIRE(n.length() == Catch::Approx(1.0));
}
