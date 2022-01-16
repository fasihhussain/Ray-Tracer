#include "Triangle.hpp"
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"

#include <math.h>

Triangle::Triangle() : Geometry(), v0(Point3D()), v1(Point3D()), v2(Point3D())
{
}

Triangle::Triangle(const Point3D &a, const Point3D &b, const Point3D &c) : Geometry(), v0(a), v1(b), v2(c)
{
}

Triangle::Triangle(const Triangle &other) : Geometry(other), v0(other.v0), v1(other.v1), v2(other.v2)
{
}

Triangle &Triangle::operator=(const Triangle &other)
{
  if (this == &other)
    return (*this);
  Geometry::operator=(other);
  v0 = other.v0;
  v1 = other.v1;
  v2 = other.v2;
  return *this;
}

std::string Triangle::to_string() const
{
  std::stringstream ss;
  ss << "Triangle: " << v0.to_string() << " " << v1.to_string()
     << " " << v2.to_string();
  return ss.str();
}

BBox Triangle::getBBox() const
{
  // Minumum coordinate bound = min(v0,v1,v2) = min(miv(v0,v1),v2)
  // Maximum coordinate bound = max(v0,v1,v2) = max(mav(v0,v1),v2)
  Point3D minpoint = min((min(v0, v1)), v2);
  Point3D maxpoint = max((max(v0, v1)), v2);
  return BBox(minpoint, maxpoint);
}

bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
  // See Ray Tracing from the Ground Up pg 362-367
  double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
  double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
  double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

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
    // Compute normal of the triangle
    Vector3D normal = (v1 - v0) ^ (v2 - v0);
    normal.normalize();
    s.is_dense_medium = false;
    s.normal = normal;
    return true;
  }
  return false;
}

Point3D Triangle::pick_random_point() const
{
    double r1 = sqrt((float) rand() / (RAND_MAX));
    double r2 = ((float) rand() / (RAND_MAX));

    return v0*(1-r1) + v1*r1*(1-r2) + v2*r2*r1;
}