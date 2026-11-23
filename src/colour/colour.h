#pragma once

// A colour with red, green and blue between 0 (none) and 1 (full).
class Colour {
public:
    Colour(double r, double g, double b);

    double r() const;
    double g() const;
    double b() const;

private:
    double _r;
    double _g;
    double _b;
};
