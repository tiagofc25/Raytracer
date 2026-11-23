#include "io/png_saver.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

namespace {

// 0..1 -> 0..255, values outside the range are clamped.
unsigned char toByte(double value) {
    double clamped = std::clamp(value, 0.0, 1.0);
    return static_cast<unsigned char>(clamped * 255.0 + 0.5);
}

}  // namespace

void PngSaver::save(const Image& image, const std::string& path) {
    std::vector<unsigned char> rgba;
    rgba.reserve(image.width() * image.height() * 4);

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& colour = image.pixel(x, y);
            rgba.push_back(toByte(colour.r()));
            rgba.push_back(toByte(colour.g()));
            rgba.push_back(toByte(colour.b()));
            rgba.push_back(255);
        }
    }

    unsigned int error = lodepng::encode(path, rgba, image.width(), image.height());
    if (error != 0) {
        throw std::runtime_error("Could not save " + path + ": " + lodepng_error_text(error));
    }
}
