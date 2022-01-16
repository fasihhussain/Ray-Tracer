#include "Phong.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"

#include <math.h>

Phong::Phong() {
  color = RGBColor(0, 0, 0);
}

Phong::Phong(float c) {
  color = RGBColor(c, c, c);
}

Phong::Phong(float r, float g, float b) {
  color = RGBColor(r, g, b);
}

Phong::Phong(const RGBColor &c) {
  color = c;
}
// Copy constructor
Phong::Phong(const Phong &other) {
  color = other.color;
}

// Assignment operator

Phong& Phong::operator=(const Phong &other) {
  if (this == &other)
    return *this;

  color = other.color;

  return *this;
}

  // Get secondary rays.
std::vector<Ray> Phong::secondary_rays(const ShadeInfo &sinfo) const {  
  std::vector<Ray> sec_ray;
  
  // no secondary rays for this material
  // recursion depth will end on this material
  return sec_ray;
}

RGBColor Phong::shade(const ShadeInfo &sinfo, const Beam beam) const {

  // a color sum of ambient, specular and diffuse components is returned
  // resource : https://en.wikipedia.org/wiki/Phong_shading

  Vector3D normal = sinfo.normal;
  normal.normalize();
  Vector3D ray = -sinfo.ray.d;
  ray.normalize();

  float t;
  Vector3D light_dir = beam.direction;

  float cos_theta = normal*light_dir;
  float cos_alpha = ray*(2 * (normal*light_dir) * normal - light_dir);

  if( cos_alpha < 0) {
    cos_alpha = 0;
  }
  
  if( cos_theta < 0) {
    cos_theta = 0;
  }

  float specular = std::pow(cos_alpha, 50);
  float diffuse = cos_theta;
  float ambient = 0.1;
  
  return diffuse * color + specular * beam.color + ambient * color;

}