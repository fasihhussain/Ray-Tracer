#include "Point3D.hpp"

Point3D::Point3D()
{
    x = y = z = 0;
}

Point3D::Point3D(float c)
{
    x = y = z = c;
}
Point3D::Point3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// String representation.
std::string Point3D::to_string() const
{
    std::string repr = "(" + std::to_string(x) +
                       ", " + std::to_string(y) +
                       ", " + std::to_string(z) + ")";
    return repr;
}

// Arithmetic.
Point3D Point3D::operator-() const
{
    return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator-(const Point3D &p) const
{
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D &v) const
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const
{
    return Point3D(x - v.x, y - v.y, z - v.z);
}

Point3D Point3D::operator*(const float s) const
{
    return Point3D(s * x, s * y, s * z);
}

// Distance between points.
float Point3D::d_squared(const Point3D &p) const
{
    return pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2);
}

float Point3D::distance(const Point3D &p) const
{
    return pow(this->d_squared(p), 0.5);
}

// Scale pt by a factor, s.
Point3D operator*(const float a, const Point3D &pt)
{
    return Point3D(a * pt.x, a * pt.y, a * pt.z);
}

// Compare points.
Point3D min(const Point3D &a, const Point3D &b)
{
    return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D &a, const Point3D &b)
{
    return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}