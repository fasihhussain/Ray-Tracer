#include "Vector3D.hpp"

// Constructors.
Vector3D::Vector3D()
{
    x = y = z = 0;
}

Vector3D::Vector3D(double c)
{
    x = y = z = c;
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3D::Vector3D(const Point3D &p)
{
    x = (double)p.x;
    y = (double)p.y;
    y = (double)p.y;
}

// Assign vector from other entitites.
Vector3D &Vector3D::operator=(const Point3D &rhs)
{
    x = (double)rhs.x;
    y = (double)rhs.y;
    y = (double)rhs.y;

    return *this;
}

// String representation.
std::string Vector3D::to_string() const
{
    std::string repr = "(" + std::to_string(x) +
                       ", " + std::to_string(y) +
                       ", " + std::to_string(z) + ")";
    return repr;
}

// Arithmetic.
Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D &v) const
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}
Vector3D &Vector3D::operator+=(const Vector3D &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3D Vector3D::operator-(const Vector3D &v) const
{
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D &Vector3D::operator-=(const Vector3D &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

// Scaling.
Vector3D Vector3D::operator*(const double a) const
{
    return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(const double a) const
{
    return Vector3D(x / a, y / a, z / a);
}
void Vector3D::normalize()
{
    double len = this->length();
    x /= len;
    y /= len;
    z /= len;
}

// Length.
double Vector3D::length() const
{
    return pow(this->len_squared(), 0.5);
}
double Vector3D::len_squared() const
{
    return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

// Vector products.
double Vector3D::operator*(const Vector3D &b) const
{
    return (x * b.x) + (y * b.y) + (z * b.z);
}
Vector3D Vector3D::operator^(const Vector3D &v) const
{
    double _x = (y * v.z) - (z * v.y);
    double _y = (z * v.x) - (x * v.z);
    double _z = (x * v.y) - (y * v.x);

    return Vector3D(_x, _y, _z);
}

Vector3D operator*(const double a, const Vector3D &v)
{
    return Vector3D(a * v.x, a * v.y, a * v.z);
}