#include "material/lambert_shader.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

// intensity = normal . (direction to the light), both of length 1.
// 1 when the surface faces the light, 0 at 90 degrees or more (no negative light).
Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();
    double intensity = std::max(0.0, hit.normal.dot(toLight));

    const Colour& lightColour = light.colour();
    return Colour(_colour.r() * lightColour.r() * intensity,
                  _colour.g() * lightColour.g() * intensity,
                  _colour.b() * lightColour.b() * intensity);
}
