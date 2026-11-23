#include "material/flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const HitInfo&, const Light&) const {
    return _colour;
}
