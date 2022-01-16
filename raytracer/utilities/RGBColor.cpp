#include "RGBColor.hpp"
#include <cmath>
#include <sstream>
// Helper function to ensure value lies between a range
float clamp(float c, float min, float max)
{
    if (c < min)
        return min;
    if (c > max)
        return max;
    return c;
}

RGBColor::RGBColor() : r(0), g(0), b(0) {}

RGBColor::RGBColor(float c)
{
    // Ensure c is between 0 and 1
    c = clamp(c, 0.0f, 1.0f);
    r = c;
    g = c;
    b = c;
}

RGBColor::RGBColor(float _r, float _g, float _b) {
    r = clamp(_r, 0.0f, 1.0f);
    g = clamp(_g, 0.0f, 1.0f);
    b = clamp(_b, 0.0f, 1.0f);

}

std::string RGBColor::to_string() const
{
    // create a string representation of the vector.
    std::stringstream ss;
    ss << int(r*255) << " " << int(g*255) << " " << int(b*255);
    return ss.str();
}

RGBColor RGBColor::operator+(const RGBColor &c) const
{
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor &RGBColor::operator+= (const RGBColor &c)
{
    r = clamp(r + c.r, 0.0f, 1.0f);
    g = clamp(g + c.g, 0.0f, 1.0f);
    b = clamp(b + c.b, 0.0f, 1.0f);
    return *this;
}

RGBColor RGBColor::operator* (const float a) const {
    return RGBColor(r * a, g * a, b * a);
}

RGBColor &RGBColor::operator*= (const float a) {
    r = clamp(r * a, 0.0f, 1.0f);
    g = clamp(g * a, 0.0f, 1.0f);
    b = clamp(b * a, 0.0f, 1.0f);
    return *this;
}

RGBColor RGBColor::operator/ (const float a) const {
    return RGBColor(r / a, g / a, b / a);
}

RGBColor &RGBColor::operator/= (const float a) {
    r = clamp(r / a, 0.0f, 1.0f);
    g = clamp(g / a, 0.0f, 1.0f);
    b = clamp(b / a, 0.0f, 1.0f);
    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const {
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator==(const RGBColor &c) const {
    return (r == c.r && g == c.g && b == c.b);
}

RGBColor RGBColor::powc(float p) const {
    return RGBColor(std::pow(r, p), std::pow(g, p), std::pow(b, p));
}

float RGBColor::average() const {
    return (r + g + b) / 3.0;
}

RGBColor operator*(const float a, const RGBColor &c) {
    return c * a;
}