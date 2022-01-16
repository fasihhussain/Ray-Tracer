#include "ReflectiveTransparent.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <iostream>

#include <math.h>

ReflectiveTransparent::ReflectiveTransparent() {
  color = RGBColor(0, 0, 0);
  refractive_index = 1.2;
}

ReflectiveTransparent::ReflectiveTransparent(float c) {
  color = RGBColor(c, c, c);
  refractive_index = 1.2;
}

ReflectiveTransparent::ReflectiveTransparent(float r, float g, float b) {
  color = RGBColor(r, g, b);
  refractive_index = 1.2;
}

ReflectiveTransparent::ReflectiveTransparent(const RGBColor &c) {
  color = c;
  refractive_index = 1.2;
}

ReflectiveTransparent::ReflectiveTransparent(const RGBColor &c, float refractive_index_) {
  color = c;
  refractive_index = refractive_index_;
}

ReflectiveTransparent::ReflectiveTransparent(const ReflectiveTransparent &other) {
  color = other.color;
  refractive_index = other.refractive_index;
}

ReflectiveTransparent& ReflectiveTransparent::operator=(const ReflectiveTransparent &other) {
  if (this == &other)
    return *this;

  color = other.color;

  return *this;
}

  // Get secondary rays.
  // sum of weights of all secondary rays should be strictly less than 1
  // otherwise scene will not converge with recursion depth.
std::vector<Ray> ReflectiveTransparent::secondary_rays(const ShadeInfo &sinfo) const {

  Ray primary_ray = sinfo.ray;
  std::vector<Ray> sec_ray;
  
  
  Vector3D normal = sinfo.normal;
  
  // cases when light enters from denser to thiner medium
  // and vice versa
  float bending;
  if ( sinfo.is_dense_medium)
  {
    bending = 1.0 / refractive_index;
  }
  else
  {
    bending = refractive_index;
    
    Ray reflected_ray;
    reflected_ray.d = primary_ray.d - 2*(sinfo.normal*primary_ray.d) * sinfo.normal;
    reflected_ray.d.normalize();

    reflected_ray.o = sinfo.hit_point + kEpsilon * sinfo.normal;

    reflected_ray.w = 0.5;

    sec_ray.push_back(reflected_ray);
  }

  float cosine_inc = -(normal*primary_ray.d);
  float sine_ref = bending*bending * (1-cosine_inc*cosine_inc);

  Ray refracted_ray;
  refracted_ray.d = bending*primary_ray.d + (bending*cosine_inc - sqrt(1 - sine_ref*sine_ref))*normal;

  refracted_ray.o = sinfo.hit_point + kEpsilon * refracted_ray.d;

  refracted_ray.w = 0.5; // this is transparency coefficient and is >=0 and <=1

  sec_ray.push_back(refracted_ray);

  return sec_ray;
}

RGBColor ReflectiveTransparent::shade(const ShadeInfo &sinfo, const Beam beam) const {
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
  
  // this is equivalent to phong shading
  return diffuse * color + specular * beam.color + ambient * color;

}