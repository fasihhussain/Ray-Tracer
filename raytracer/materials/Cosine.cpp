#include "Cosine.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
Cosine::Cosine() {
  color = RGBColor(0, 0, 0);
}

Cosine::Cosine(float c) {
  color = RGBColor(c, c, c);
}

Cosine::Cosine(float r, float g, float b) {
  color = RGBColor(r, g, b);
}

Cosine::Cosine(const RGBColor &c) {
  color = c;
}
// Copy constructor
Cosine::Cosine(const Cosine &other) {
  color = other.color;
}

// Assignment operator

Cosine& Cosine::operator=(const Cosine &other) {
  if (this == &other)
    return *this;

  color = other.color;

  return *this;
}

  // Get secondary rays.
std::vector<Ray> Cosine::secondary_rays(const ShadeInfo &sinfo) const {  
  std::vector<Ray> sec_ray;
  
  return sec_ray;
}

RGBColor Cosine::shade(const ShadeInfo &sinfo, const Beam beam) const {
  Vector3D normal = sinfo.normal;
  normal.normalize();
  Vector3D ray = -sinfo.ray.d;
  ray.normalize();
  float cos_theta = normal*ray;
  return color * cos_theta;
}