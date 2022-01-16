#include "Ray.hpp"

// Constructors.
Ray::Ray()
{
    o = Point3D();
    d = Vector3D();
    w = 1;
}

Ray::Ray(const Point3D &origin, const Vector3D &dir)
{
    o = origin;
    d = dir;
    w = 1;

    d.normalize();
}

// String representation.
std::string Ray::to_string() const
{
    std::string repr = "o" + o.to_string() +
                       " d" + d.to_string() +
                       " w(" + std::to_string(w) + ")";
    return repr;
}