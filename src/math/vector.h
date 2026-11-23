#pragma once

// A 3D vector: used for points, directions and normals.
class Vector {
public:
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;  // v * 2

    double dot(const Vector& other) const;
    double length() const;
    Vector normalised() const;

private:
    double _x;
    double _y;
    double _z;
};

// 2 * v: the number is on the left, so this cannot be a member function.
Vector operator*(double scalar, const Vector& vector);
