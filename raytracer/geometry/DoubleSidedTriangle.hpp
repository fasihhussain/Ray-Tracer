#pragma once

/**
   This file declares the DoubleSidedTriangle class which represents a DoubleSidedTriangle defined by
   its 3 vertices.

   Courtesy Kevin Suffern.
*/

#include "Geometry.hpp"

#include "../utilities/Point3D.hpp"

class DoubleSidedTriangle : public Geometry {
protected:
  Point3D v0, v1, v2; // the vertices. they must not be colinear.

public:
  // Constructors. Passed vertices are assumed to be ordered for orientation,
  DoubleSidedTriangle(); // DoubleSidedTriangle with vertices at origin.
  DoubleSidedTriangle(const Point3D &, const Point3D &, const Point3D &); // set vertices.

  // Copy constructor and assignment operator.
  DoubleSidedTriangle(const DoubleSidedTriangle &object);
  DoubleSidedTriangle &operator=(const DoubleSidedTriangle &rhs);

  // Destructor.
  virtual ~DoubleSidedTriangle() = default;

  // String representation.
  std::string to_string() const override;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, float &t, ShadeInfo &s) const override;

  // Get bounding box.
  virtual BBox getBBox() const override;
  
  // Pick random point uniformly
  virtual Point3D pick_random_point() const override;
};
