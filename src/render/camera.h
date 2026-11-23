#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "image/image.h"
#include "math/vector.h"
#include "scene/scene.h"

// A pinhole camera. For now it always looks along the positive Z axis,
// at a screen placed at distance 1 in front of it.
class Camera {
public:
    explicit Camera(const Vector& position);

    const Vector& position() const;

    // The ray from the camera through the center of pixel (x, y).
    // screenWidth is the width of the screen in world units; its height
    // follows the image's proportions. The direction is not normalised.
    Ray rayThroughPixel(unsigned int x, unsigned int y,
                        unsigned int imageWidth, unsigned int imageHeight,
                        double screenWidth) const;

    // The colour seen along one ray: the sky if nothing is hit, black if the
    // hit point is in shadow, otherwise the colour given by its material.
    Colour trace(const Ray& ray, const Scene& scene) const;

    // Fill every pixel of the image.
    void render(Image& image, const Scene& scene, double screenWidth) const;

private:
    Vector _position;
};
