#pragma once

#include <vector>

#include "colour/colour.h"

// A grid of pixels. (0, 0) is the top left corner; x is the column, y the row.
class Image {
public:
    Image(unsigned int width, unsigned int height);  // every pixel starts black

    unsigned int width() const;
    unsigned int height() const;

    void setPixel(unsigned int x, unsigned int y, const Colour& colour);
    const Colour& pixel(unsigned int x, unsigned int y) const;

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;  // row after row, from the top
};
