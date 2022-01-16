#include "RGBColor.hpp"

// Constructors.
RGBColor::RGBColor()
{
    r = g = b = 0;
}

RGBColor::RGBColor(float c)
{
    r = g = b = c;
}

RGBColor::RGBColor(float _r, float _g, float _b)
{
    r = _r;
    g = _g;
    b = _b;
}

// String representation.
std::string RGBColor::to_string() const
{
    std::string repr = "(" + std::to_string(r) +
                       ", " + std::to_string(g) +
                       ", " + std::to_string(b) + ")";
    return repr;
}

// Operations.
RGBColor RGBColor::operator+(const RGBColor &c) const
{
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor &RGBColor::operator+=(const RGBColor &c)
{
    r += c.r;
    g += c.g;
    b += c.b;

    return *this;
}

RGBColor RGBColor::operator*(const float a) const
{
    return RGBColor(r * a, g * a, b * a);
}

RGBColor &RGBColor::operator*=(const float a)
{
    r *= a;
    g *= a;
    b *= a;

    return *this;
}

RGBColor RGBColor::operator/(const float a) const
{
    return RGBColor(r / a, g / a, b / a);
}

RGBColor &RGBColor::operator/=(const float a)
{
    r /= a;
    g /= a;
    b /= a;

    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const
{
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator==(const RGBColor &c) const
{
    return (r == c.r) && (g == c.g) && (b == c.b);
}

RGBColor RGBColor::powc(float p) const
{
    return RGBColor(pow(r, p), pow(g, p), pow(b, p));
}

float RGBColor::average() const
{
    return (r + g + b) / 3;
}

RGBColor operator*(const float a, const RGBColor &c)
{
    return RGBColor(a * c.r, a * c.g, a * c.b);
}