#pragma once

#include "io/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(const Image& image, const std::string& path) override;
};
