#include "DoubleSidedCurvedTriangle.hpp"
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
DoubleSidedCurvedTriangle::DoubleSidedCurvedTriangle() : Geometry(), v0(Point3D()), v1(Point3D()), v2(Point3D()), v0_n(Vector3D()), v1_n(Vector3D()), v2_n(Vector3D()){}


DoubleSidedCurvedTriangle::DoubleSidedCurvedTriangle(const Point3D &a, const Point3D &b, const Point3D &c,const Vector3D &a_n,const Vector3D &b_n,const Vector3D &c_n ) : Geometry(), v0(a), v1(b), v2(c), v0_n(a_n), v1_n(b_n), v2_n(c_n){}


DoubleSidedCurvedTriangle::DoubleSidedCurvedTriangle(const DoubleSidedCurvedTriangle &other) : Geometry(other), v0(other.v0), v1(other.v1), v2(other.v2), v0_n(other.v0_n), v1_n(other.v1_n), v2_n(other.v2_n){}


DoubleSidedCurvedTriangle &DoubleSidedCurvedTriangle::operator=(const DoubleSidedCurvedTriangle &other)
{
  if (this == &other)
    return (*this);
  Geometry::operator=(other);
  v0 = other.v0;
  v1 = other.v1;
  v2 = other.v2;
  v0_n = other.v0_n;
  v1_n = other.v1_n;
  v2_n = other.v2_n;
  return *this;
}

std::string DoubleSidedCurvedTriangle::to_string() const
{
  std::stringstream ss;
  ss << "Triangle: " << v0.to_string() << " " << v1.to_string()
     << " " << v2.to_string() << "Normals: " << v0_n.to_string() << " " << v1_n.to_string() << " " << v2_n.to_string(); 
  return ss.str();
}

BBox DoubleSidedCurvedTriangle::getBBox() const
{
  // Minumum coordinate bound = min(v0,v1,v2) = min(miv(v0,v1),v2)
  // Maximum coordinate bound = max(v0,v1,v2) = max(mav(v0,v1),v2)
  Point3D minpoint = min((min(v0, v1)), v2);
  Point3D maxpoint = max((max(v0, v1)), v2);
  return BBox(minpoint, maxpoint);
}

bool DoubleSidedCurvedTriangle::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
  Vector3D norm = (v1 - v0) ^ (v2 - v0);
  Point3D V0 = v0, V1 = v1, V2 = v2;
  Vector3D V0_N = v0_n, V1_N = v1_n, V2_N = v2_n;
  bool is_dense = false;

  if ( (norm*ray.d) > 0) {
    V0 = v1;
    V0_N = v1_n;

    V1 = v0;
    V1_N = v0_n;

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
    // Compute normal of the triangle
    Vector3D normal((1-beta-gamma)*V0_N + beta*V1_N + gamma*V2_N);
    normal.normalize();
    s.normal = normal;
    s.is_dense_medium = is_dense;
    return true;
  }
  return false;
}