#include "Jittered.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"
#include "../cameras/Camera.hpp"
#include <cstdlib>
#include "../utilities/Constants.hpp"
Jittered::Jittered(Camera *c_ptr, ViewPlane *v_ptr,int n) : Sampler(c_ptr, v_ptr),n(n)
{
}

Jittered::Jittered(): Sampler(),n(1) {

}
Jittered::Jittered(int n): Sampler(),n(n) {

}
Jittered::Jittered(const Jittered &camera) : Sampler(camera)
{
  this->n = camera.n;
}
Jittered &Jittered::operator=(const Jittered &other)
{
  if (this == &other)
    return (*this);

  Sampler::operator=(other);
  this->n = other.n;

  return (*this);
}

std::vector<Ray> Jittered::get_rays(int px, int py) const
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
  // Create n^2 rays
  for (int p = 0; p < n; p++) {

    for (int q = 0; q < n; q++) {
      // Find the x and y coordinates of the sample point on the grid
      samplePoint.x = x_spacing * (px+ (p+rand()*invRAND_MAX)/n);
      samplePoint.y = y_spacing * (py+ (q+rand()*invRAND_MAX)/n);
      // Find the x and y coordinates of the sample point on the image plane

      Point3D ray_origin  = top_left + samplePoint;
      // Get the direction of the ray to shoot and after making the ray
      // set the weight, and add it to the vector
      Vector3D ray_direction = camera_ptr->get_direction(ray_origin);
      Ray ray_to_push(ray_origin, ray_direction);
      ray_to_push.w = 1.0/(n*n);
      rays.push_back(ray_to_push);

    }
  }
  return rays;
}