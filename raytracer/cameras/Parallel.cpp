#include "Parallel.hpp"

Parallel::Parallel(void)
    : Camera()
{
}

Parallel::Parallel(float c)
    : Camera()
{
  dir = Vector3D(c);
}

Parallel::Parallel(float x, float y, float z)
    : Camera()
{
  dir = Vector3D(x, y, z);
  // Convert dir to unit vector.
  dir.normalize();
}

Parallel::Parallel(const Parallel& camera)
    : Camera(camera),dir(camera.dir)
{
}
Parallel::Parallel(const Vector3D& d) {
  dir = d;
  // Convert dir to unit vector.
  dir.normalize();
}

Parallel & Parallel::operator=(const Parallel &other) {
  if (this != &other) {
    Camera::operator=(other);
    dir = other.dir;
  }
  return *this;
}

Vector3D Parallel::get_direction(const Point3D& p) const {
  // Return the direction of projection. (Same for each point)
  return dir;
}