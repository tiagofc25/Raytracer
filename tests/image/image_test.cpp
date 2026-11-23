#include <catch2/catch_test_macros.hpp>

#include "image/image.h"

TEST_CASE("An image knows its width and height") {
    Image image(5, 4);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 4);
}

TEST_CASE("setPixel(3, 2) sets the pixel at column 3, row 2, and the others stay black") {
    Image image(5, 4);

    image.setPixel(3, 2, Colour(1, 0.5, 0.25));

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& colour = image.pixel(x, y);
            if (x == 3 && y == 2) {
                REQUIRE(colour.r() == 1);
                REQUIRE(colour.g() == 0.5);
                REQUIRE(colour.b() == 0.25);
            } else {
                REQUIRE(colour.r() == 0);
                REQUIRE(colour.g() == 0);
                REQUIRE(colour.b() == 0);
            }
        }
    }
}
