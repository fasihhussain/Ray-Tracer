#include "Plane.hpp"
#include <sstream>
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"
Plane::Plane() {
  a = Point3D(0, 0, 0);
  n = Vector3D(0, 1,0);
}
Plane::Plane(const Point3D &pt, const Vector3D &n) {
  this->a = pt;
  this->n = n;
  // Store normalized vector
  this->n.normalize();
}

Plane::Plane(const Plane &object) {
  a = object.a;
  n = object.n;
}
Plane &Plane::operator=(const Plane &rhs) {
  if (this == &rhs)
    return *this;
  a = rhs.a;
  n = rhs.n;
  return *this;
}

std::string Plane::to_string() const {
  std::stringstream ss;
  ss << "Plane: Point:" << a.to_string() << "\nNormal:" << n.to_string();
  return ss.str();  // return the string
}

// Returns whether a ray hits a plane or not and if it does, store the time of intersection (t) in t and update ShadeInfo
// @param ray: ray to be checked
// @param t: current t of intersection. If no intersection, set as kHugeValue
// @param s: Shading Information regarding the ray
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  // See if a hit is possible or not, denom != 0
  double denom = ray.d * n;

  if (denom == 0) {
    return false;
  }

  // Compute possible intersection point.
  // Source: Ray Tracing from the Ground Up, page 56
  double possiblet = (a - ray.o)*n / denom;

  // If we have a better t, update the ShadeInfo and t
  if (possiblet > kEpsilon && possiblet<t) {
    t = possiblet;
    s.normal = n;
    s.depth = 0;
    s.hit = true;
    s.t = t;
    s.hit_point = ray.o + t * ray.d;
    s.material_ptr = material_ptr;
    s.ray = ray;
    return true;
    s.is_dense_medium = false;
  }
  else {
    return false;
  }

}

BBox Plane::getBBox() const {
  // Return a garbage Bounding Box since planes can not be bounded
  // Bounding box of volume 0
  return BBox(a, a);
}