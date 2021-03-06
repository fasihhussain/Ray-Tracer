#include "Parallel.hpp"

Parallel::Parallel()
{
    dir = Vector3D(0, 0, -1);
}

Parallel::Parallel(float c)
{
    dir = Vector3D(c, c, c);
    dir.normalize();
}

Parallel::Parallel(float x, float y, float z)
{
    dir = Vector3D(x, y, z);
    dir.normalize();
}
  
Parallel::Parallel(const Vector3D &d)
{
    dir = d;
    dir.normalize();
}

Parallel::Parallel(const Parallel &camera)
{
    dir = camera.dir;
}

Parallel &Parallel::operator=(const Parallel &other)
{
    dir = other.dir;
    return *this;
}

Vector3D Parallel::get_direction(const Point3D &p) const
{
    return dir;
}