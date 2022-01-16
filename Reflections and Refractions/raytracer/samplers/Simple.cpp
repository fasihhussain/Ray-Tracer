#include "Simple.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"
#include "../cameras/Camera.hpp"
Simple::Simple(Camera *c_ptr, ViewPlane *v_ptr) : Sampler(c_ptr, v_ptr)
{
}

Simple::Simple(const Simple &camera) : Sampler(camera)
{
}
Simple &Simple::operator=(const Simple &other)
{
  if (this == &other)
    return (*this);

  Sampler::operator=(other);

  return (*this);
}

std::vector<Ray> Simple::get_rays(int px, int py) const
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
  Vector3D offset(x_spacing * (px+0.5), y_spacing * (py+0.5), 0);
  Point3D ray_origin  = top_left + offset;
  // Push the ray and return the vector
  Vector3D ray_direction = camera_ptr->get_direction(ray_origin);
  rays.push_back(Ray(ray_origin, ray_direction));
  return rays;
}