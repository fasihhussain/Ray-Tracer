#pragma once

/**
   This file declares the Sphere class which represents a sphere defined by its
   center and radius.

   Courtesy Kevin Suffern.
*/

#include "Geometry.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/ShadeInfo.hpp"

class Sphere : public Geometry {
protected:
  Point3D c; // center.
  float r;   // radius.

public:
  // Constructors.
  Sphere(); // sphere at origin with radius 0.
  Sphere(const Point3D &center, float radius); // set center and radius,

  // Copy constructor and assignment operator.
  Sphere(const Sphere &object);
  Sphere &operator=(const Sphere &rhs);

  // Destructor.
  virtual ~Sphere() = default;

  // String representation.
  std::string to_string() const override;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, float &t, ShadeInfo &s) const override;

  // Get bounding box.
  virtual BBox getBBox() const override;
  
  // Get area.
  virtual float get_area() const override;

  // Pick random point uniformly
  virtual Point3D pick_random_point() const override;
};
