#include "RandomSampler.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"
#include "../cameras/Camera.hpp"

#include <cstdlib>
#include "../utilities/Constants.hpp"
RandomSampler::RandomSampler(Camera *c_ptr, ViewPlane *v_ptr,int n) : Sampler(c_ptr, v_ptr),n(n)
{
}

RandomSampler::RandomSampler(): Sampler(),n(1) {

}
RandomSampler::RandomSampler(int n): Sampler(),n(n) {

}
RandomSampler::RandomSampler(const RandomSampler &camera) : Sampler(camera)
{
  this->n = camera.n;
}
RandomSampler &RandomSampler::operator=(const RandomSampler &other)
{
  if (this == &other)
    return (*this);

  Sampler::operator=(other);
  this->n = other.n;

  return (*this);
}

std::vector<Ray> RandomSampler::get_rays(int px, int py) const
{
  // Create a vector to hold the rays
  std::vector<Ray> rays;
  // See if we have a camera and a viewplane
  if (viewplane_ptr == NULL || camera_ptr == NULL)
    return rays;

  Point3D top_left = viewplane_ptr->top_left;
  Point3D bottom_right = viewplane_ptr->bottom_right;
  int hres = viewplane_ptr->hres;
  int vres = viewplane_ptr->vres;
  // Find out how much to move the ray's origin in x and y
  float x_spacing = (bottom_right.x - top_left.x) / hres;
  float y_spacing = (bottom_right.y - top_left.y) / vres;
  
  Point3D samplePoint;
  // We will be creating n^2 rays
  for (int p = 0; p < n; p++) {

    for (int q = 0; q < n; q++) {
      // Find the x and y coordinates of the sample point
      samplePoint.x = x_spacing * (px+ rand()*invRAND_MAX);
      samplePoint.y = y_spacing * (py+ rand()*invRAND_MAX);
      Point3D ray_origin  = top_left + samplePoint;
      // Get the direction of the ray to shoot and after making the ray
      // set the weight, and add it to the vector
      Vector3D ray_direction = camera_ptr->get_direction(ray_origin);
      Ray ray_to_shoot(ray_origin, ray_direction);

      ray_to_shoot.w = 1.0/(n*n);
      rays.push_back(ray_to_shoot);

    }
  }
  return rays;
}