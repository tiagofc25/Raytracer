#include "render/camera.h"

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const { return _position; }

Ray Camera::rayThroughPixel(unsigned int x, unsigned int y,
                            unsigned int imageWidth, unsigned int imageHeight,
                            double screenWidth) const {
    double pixelSize = screenWidth / imageWidth;
    double screenHeight = pixelSize * imageHeight;

    // Center of the pixel, measured from the center of the screen.
    // Image rows go down, but world Y goes up, hence the minus sign.
    double screenX = (x + 0.5) * pixelSize - screenWidth / 2.0;
    double screenY = screenHeight / 2.0 - (y + 0.5) * pixelSize;

    return Ray(_position, Vector(screenX, screenY, 1.0));
}

Colour Camera::trace(const Ray& ray, const Sphere& sphere, const Light& light) const {
    std::optional<HitInfo> hit = sphere.intersect(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material->shade(*hit, light);
}

void Camera::render(Image& image, const Sphere& sphere, const Light& light, double screenWidth) const {
    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            Ray ray = rayThroughPixel(x, y, image.width(), image.height(), screenWidth);
            image.setPixel(x, y, trace(ray, sphere, light));
        }
    }
}
