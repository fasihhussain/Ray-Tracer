#include "BBox.hpp"
#include "Ray.hpp"
#include "Constants.hpp"
#include "../geometry/Geometry.hpp"
#include <sstream>
#include <iostream>
BBox::BBox(const Point3D &min, const Point3D &max)
{
  pmin = min;
  pmax = max;
}

std::string BBox::to_string() const
{
  std::stringstream ss;
  ss << "BBox[" << pmin.to_string() << ", " << pmax.to_string() << "]";
  return ss.str();
}

bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const
{
  // Get ray's origin and direction
  double ox = ray.o.x;
  double oy = ray.o.y;
  double oz = ray.o.z;
  double dx = ray.d.x;
  double dy = ray.d.y;
  double dz = ray.d.z;
  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  if (dx == 0)
  {
    // If the ray doesn't move in the x direction
    // see if it hits the x-bounds
    if (ox < pmin.x || ox > pmax.x)
      return false;
    tx_min = -kHugeValue;
    tx_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    tx_min = (pmin.x - ox) / dx;
    tx_max = (pmax.x - ox) / dx;

    // if min > max, then swap so limits are correct
    if (tx_min > tx_max)
      std::swap(tx_min, tx_max);
  }

  if (dy == 0)
  {
    // If the ray doesn't move in the y direction
    // see if it hits the y-bounds
    if (oy < pmin.y || oy > pmax.y)
      return false;
    ty_min = -kHugeValue;
    ty_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    ty_min = (pmin.y - oy) / dy;
    ty_max = (pmax.y - oy) / dy;
    // if min > max, then swap so limits are correct
    if (ty_min > ty_max)
      std::swap(ty_min, ty_max);
  }

  if (dz == 0)
  {
    // If the ray doesn't move in the z direction
    // see if it hits the z-bounds

    if (oz < pmin.z || oz > pmax.z)
      return false;
    tz_min = -kHugeValue;
    tz_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    tz_min = (pmin.z - oz) / dz;
    tz_max = (pmax.z - oz) / dz;

    // if min > max, then swap so limits are correct
    if (tz_min > tz_max)
      std::swap(tz_min, tz_max);
  }
  // std::cout << "end me" << std::endl;
  double t0, t1;

  // Find the largest entering t value
  if (tx_min > ty_min)
    t0 = tx_min;
  else
    t0 = ty_min;

  if (tz_min > t0)
    t0 = tz_min;

  // find the smallest exiting t value
  if (tx_max < ty_max)
    t1 = tx_max;
  else
    t1 = ty_max;

  if (tz_max < t1)
    t1 = tz_max;

  // std::cout << tx_max << " " << ty_max << " " << tz_max << std::endl;
  // If the range is valid and the intersection contains
  // a point > kEpsilon, then there is an intersection
  bool ans = (t0 <= t1 && t1 > kEpsilon);
  // std::cout << "I made it here. " << "t0:" << t0 << "t1:" << t1 <<std::endl;
  if (ans)
  {
    // If hit, then set values
    t_enter = t0;
    t_exit = t1;
  }
  // Return whether there was a hit or not
  return ans;
}

bool BBox::contains(const Point3D &p) const
{
  // See if the point is within the bounds
  return p.x >= pmin.x && p.x <= pmax.x &&
         p.y >= pmin.y && p.y <= pmax.y &&
         p.z >= pmin.z && p.z <= pmax.z;
}

void BBox::extend(Geometry *g)
{

  BBox extendby = g->getBBox();
  extend(extendby);
}

void BBox::extend(const BBox &b)
{
  // Extend the bounds so that the min/max bounds of the box b
  // are also covered
  pmin = min(pmin, b.pmin);
  pmax = max(pmax, b.pmax);
}

bool BBox::overlaps(Geometry *g)
{

  BBox b = g->getBBox();
  return overlaps(b);
}

bool BBox::overlaps(const BBox &b)
{
  // See if the bounds overlap by seeing if each component overlaps
  return (pmin.x <= b.pmax.x && pmax.x >= b.pmin.x &&
          pmin.y <= b.pmax.y && pmax.y >= b.pmin.y &&
          pmin.z <= b.pmax.z && pmax.z >= b.pmin.z);
}

bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit, float &tx_min,
           float &tx_max, float &ty_min, float &ty_max, float &tz_min,
           float &tz_max) const
{
    // Get ray's origin and direction
  double ox = ray.o.x;
  double oy = ray.o.y;
  double oz = ray.o.z;
  double dx = ray.d.x;
  double dy = ray.d.y;
  double dz = ray.d.z;

  if (dx == 0)
  {
    // If the ray doesn't move in the x direction
    // see if it hits the x-bounds
    if (ox < pmin.x || ox > pmax.x)
      return false;
    tx_min = -kHugeValue;
    tx_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    tx_min = (pmin.x - ox) / dx;
    tx_max = (pmax.x - ox) / dx;

    // if min > max, then swap so limits are correct
    if (tx_min > tx_max)
      std::swap(tx_min, tx_max);
  }

  if (dy == 0)
  {
    // If the ray doesn't move in the y direction
    // see if it hits the y-bounds
    if (oy < pmin.y || oy > pmax.y)
      return false;
    ty_min = -kHugeValue;
    ty_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    ty_min = (pmin.y - oy) / dy;
    ty_max = (pmax.y - oy) / dy;
    // if min > max, then swap so limits are correct
    if (ty_min > ty_max)
      std::swap(ty_min, ty_max);
  }

  if (dz == 0)
  {
    // If the ray doesn't move in the z direction
    // see if it hits the z-bounds

    if (oz < pmin.z || oz > pmax.z)
      return false;
    tz_min = -kHugeValue;
    tz_max = kHugeValue;
  }
  else
  {
    // Compute when it hits the slabs.
    tz_min = (pmin.z - oz) / dz;
    tz_max = (pmax.z - oz) / dz;

    // if min > max, then swap so limits are correct
    if (tz_min > tz_max)
      std::swap(tz_min, tz_max);
  }
  // std::cout << "end me" << std::endl;
  double t0, t1;

  // Find the largest entering t value
  if (tx_min > ty_min)
    t0 = tx_min;
  else
    t0 = ty_min;

  if (tz_min > t0)
    t0 = tz_min;

  // find the smallest exiting t value
  if (tx_max < ty_max)
    t1 = tx_max;
  else
    t1 = ty_max;

  if (tz_max < t1)
    t1 = tz_max;

  // std::cout << tx_max << " " << ty_max << " " << tz_max << std::endl;
  // If the range is valid and the intersection contains
  // a point > kEpsilon, then there is an intersection
  bool ans = (t0 <= t1 && t1 > kEpsilon);
  // std::cout << "I made it here. " << "t0:" << t0 << "t1:" << t1 <<std::endl;
  if (ans)
  {
    // If hit, then set values
    t_enter = t0;
    t_exit = t1;
  }
  // Return whether there was a hit or not
  return ans;
}