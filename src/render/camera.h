#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "light/light.h"
#include "math/vector.h"

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

    // The colour seen along one ray: the sphere's material if it is hit, black otherwise.
    Colour trace(const Ray& ray, const Sphere& sphere, const Light& light) const;

    // Fill every pixel of the image.
    void render(Image& image, const Sphere& sphere, const Light& light, double screenWidth) const;

private:
    Vector _position;
};
