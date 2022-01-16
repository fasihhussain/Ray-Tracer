#include "Reflective.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"

#include <math.h>

Reflective::Reflective() {
  color = RGBColor(0, 0, 0);
}

Reflective::Reflective(float c) {
  color = RGBColor(c, c, c);
}

Reflective::Reflective(float r, float g, float b) {
  color = RGBColor(r, g, b);
}

Reflective::Reflective(const RGBColor &c) {
  color = c;
}

Reflective::Reflective(const Reflective &other) {
  color = other.color;
}

Reflective& Reflective::operator=(const Reflective &other) {
  if (this == &other)
    return *this;

  color = other.color;

  return *this;
}

  // cast a reflected ray of weight 1/2
std::vector<Ray> Reflective::secondary_rays(const ShadeInfo &sinfo) const {  
  Ray primary_ray = sinfo.ray;
  std::vector<Ray> sec_ray;

  Ray ref_ray;
  ref_ray.d = primary_ray.d - 2*(sinfo.normal*primary_ray.d) * sinfo.normal;
  ref_ray.o = sinfo.hit_point + kEpsilon*ref_ray.d;
  ref_ray.w = 0.7;
  sec_ray.push_back(ref_ray);
  return sec_ray;
}

  // this is equivalent to phong shading
RGBColor Reflective::shade(const ShadeInfo &sinfo, const Beam beam) const {
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