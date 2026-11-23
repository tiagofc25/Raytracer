#include "math/vector.h"

#include <cmath>

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Vector::x() const { return _x; }
double Vector::y() const { return _y; }
double Vector::z() const { return _z; }

Vector Vector::operator+(const Vector& other) const {
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(_x - other._x, _y - other._y, _z - other._z);
}

Vector Vector::operator*(double scalar) const {
    return Vector(_x * scalar, _y * scalar, _z * scalar);
}

double Vector::dot(const Vector& other) const {
    return _x * other._x + _y * other._y + _z * other._z;
}

double Vector::length() const {
    return std::sqrt(dot(*this));
}

Vector Vector::normalised() const {
    return *this * (1.0 / length());
}

Vector operator*(double scalar, const Vector& vector) {
    return vector * scalar;
}
