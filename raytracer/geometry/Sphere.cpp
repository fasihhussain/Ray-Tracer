#include "Sphere.hpp"
#include <cmath>
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Math.hpp"
#include <iostream>
Sphere::Sphere() : Geometry(), c(Point3D(0, 0, 0)), r(0) {}

Sphere::Sphere(const Point3D &center, float radius) : Geometry(), c(center), r(radius){}; // set center and radius,

Sphere::Sphere(const Sphere &object) : Geometry(object), c(object.c), r(object.r){};

Sphere &Sphere::operator=(const Sphere &rhs)
{
  if (this == &rhs)
    return *this;
  Geometry::operator=(rhs);
  c = rhs.c;
  r = rhs.r;
  return *this;
}

std::string Sphere::to_string() const
{
  std::stringstream ss;
  ss << "Sphere: Center:" << c.to_string() << "\nRadius:" << r;
  return ss.str(); // return the string
}

bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const
{

  double current_t;
  // Get the vector from ray's origin to the sphere's center
  Vector3D temp = ray.o - c;
  // Compute a,b,c coefficients for the quadratic equation
  // See Ray Tracing from the Ground Up Pg 57 for details
  double a = ray.d * ray.d;
  double b = 2 * (ray.d * temp);
  double c = temp * temp - r * r;
  double discriminant = b * b - 4 * a * c;

  // If the discriminant is negative, there are no hits
  if (discriminant < 0)
    return false;
  else
  {
    // Compute the two solutions
    double e = std::sqrt(discriminant);
    double denom = 2 * a;
    current_t = (-b - e) / denom;
    // See if the first solution (The smaller one) is a "valid hit"
    // "Valid hit" is one that is > kEpsilon and < kHugeValue and 
    // earlier than the currently found hit. 
    // Since t is initialized as kHugeValue, 
    // we don't need to see < kHugeValue condition
    if (current_t > kEpsilon && current_t < t)
    {
      // If so, update the ShadeInfo, t and return true
      t = current_t;
      s.normal = (temp + t * ray.d) / r;
      s.hit_point = ray.o + t * ray.d;
      s.hit = true;
      s.depth = 0;
      s.material_ptr = material_ptr;
      s.ray = ray;
      s.t = t;
      s.is_dense_medium = false;
      return true;
    }

    current_t = (-b + e) / denom;
    // If the first solution is not the hit, then see 
    // if the second solution (larger one) is a valid hit

    if (current_t > kEpsilon && current_t < t)
    {
      // If so, update the ShadeInfo, t and return true
      t = current_t;
      s.normal = -(temp + t * ray.d) / r;
      s.hit_point = ray.o + t * ray.d;
      s.hit = true;
      s.depth = 1;
      s.material_ptr = material_ptr;
      s.ray = ray;
      s.t = t;
      s.is_dense_medium = true;
      return true;
    }
    return false;
  }
}

// Pick random point uniformly
Point3D Sphere::pick_random_point() const
{
    double x = sampleNormal(),y = sampleNormal(),z = sampleNormal();
    Vector3D v(x, y, z);
    v.normalize();
    Point3D sample = this->c + r*v;
    // std::cout << sample.to_string() << std::endl;
    return this->c + r*v;
}

BBox Sphere::getBBox() const
{
  // https://gamedev.stackexchange.com/questions/159710/getting-the-bounding-box-of-a-sphere
  // min coordinate bounds= center - (radius,radius,radius)
  // max coordinate bounds = center + (radius,radius,radius)
  Vector3D offset = Vector3D(r);
  return BBox(c - offset, c + offset);
}
