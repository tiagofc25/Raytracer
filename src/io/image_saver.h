#pragma once

#include <string>

#include "image/image.h"

// Strategy: one way of writing an image to disk. Each file format is a subclass.
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(const Image& image, const std::string& path) = 0;
};
