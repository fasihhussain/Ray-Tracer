#include "DoubleSidedTriangle.hpp"
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"

#include <math.h>

DoubleSidedTriangle::DoubleSidedTriangle() : Geometry(), v0(Point3D()), v1(Point3D()), v2(Point3D())
{
}

DoubleSidedTriangle::DoubleSidedTriangle(const Point3D &a, const Point3D &b, const Point3D &c) : Geometry(), v0(a), v1(b), v2(c)
{
}

DoubleSidedTriangle::DoubleSidedTriangle(const DoubleSidedTriangle &other) : Geometry(other), v0(other.v0), v1(other.v1), v2(other.v2)
{
}

DoubleSidedTriangle &DoubleSidedTriangle::operator=(const DoubleSidedTriangle &other)
{
  if (this == &other)
    return (*this);
  Geometry::operator=(other);
  v0 = other.v0;
  v1 = other.v1;
  v2 = other.v2;
  return *this;
}

std::string DoubleSidedTriangle::to_string() const
{
  std::stringstream ss;
  ss << "DoubleSidedTriangle: " << v0.to_string() << " " << v1.to_string()
     << " " << v2.to_string();
  return ss.str();
}

BBox DoubleSidedTriangle::getBBox() const
{
  // Minumum coordinate bound = min(v0,v1,v2) = min(miv(v0,v1),v2)
  // Maximum coordinate bound = max(v0,v1,v2) = max(mav(v0,v1),v2)
  Point3D minpoint = min((min(v0, v1)), v2);
  Point3D maxpoint = max((max(v0, v1)), v2);
  return BBox(minpoint, maxpoint);
}

bool DoubleSidedTriangle::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
  Vector3D norm = (v1 - v0) ^ (v2 - v0);
  Point3D V0 = v0, V1 = v1, V2 = v2;
  bool is_dense = false;
  
  if (norm * ray.d > 0) {
    V0 = v1;
    V1 = v0;
    is_dense = true;
  }

  // See Ray Tracing from the Ground Up pg 362-367
  double a = V0.x - V1.x, b = V0.x - V2.x, c = ray.d.x, d = V0.x - ray.o.x;
  double e = V0.y - V1.y, f = V0.y - V2.y, g = ray.d.y, h = V0.y - ray.o.y;
  double i = V0.z - V1.z, j = V0.z - V2.z, k = ray.d.z, l = V0.z - ray.o.z;

  double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  double q = g * i - e * k, sl = e * j - f * i;

  double inv_denom = 1.0 / (a * m + b * q + c * sl);

  double e1 = d * m - b * n - c * p;
  double beta = e1 * inv_denom;

  // No hit if beta is negative
  if (beta < 0.0)
    return false;

  double r = e * l - h * i;
  double e2 = a * n + d * q + c * r;
  double gamma = e2 * inv_denom;

  // No hit if gamma is negative
  if (gamma < 0.0)
    return false;

  // The barycentric coordinates must be positive,
  // if beta + gamma > 1, the 3rd value is <0
  if (beta + gamma > 1.0)
    return false;

  double e3 = a * p - b * r + d * sl;
  double t_ = e3 * inv_denom;

  // if t < kEpsilon, not a valid collision
  if (t_ < kEpsilon)
    return false;

  // if t is less than the current t, update the t and the shade info
  // and return true else false
  if (t_ < t)
  {
    t = t_;
    s.hit_point = ray.o + t * ray.d;
    s.hit = true;
    s.depth = 1;
    s.material_ptr = material_ptr;
    s.ray = ray;
    s.t = t;
    // Compute normal of the DoubleSidedTriangle
    Vector3D normal = (V1 - V0) ^ (V2 - V0);
    normal.normalize();
    s.normal = normal;
    s.is_dense_medium = is_dense;
    return true;
  }
  return false;
}

Point3D DoubleSidedTriangle::pick_random_point() const
{
    double r1 = sqrt((float) rand() / (RAND_MAX));
    double r2 = ((float) rand() / (RAND_MAX));

    return v0*(1-r1) + v1*r1*(1-r2) + v2*r2*r1;
}