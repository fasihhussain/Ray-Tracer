#pragma once

/**
   This file declares the Triangle class which represents a triangle defined by
   its 3 vertices.

   Courtesy Kevin Suffern.
*/

#include "Geometry.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
class CurvedTriangle : public Geometry {
protected:
  Point3D v0, v1, v2; // the vertices. they must not be colinear.
  Vector3D v0_n, v1_n, v2_n; // the normals at the vertices.
public:
  // Constructors. Passed vertices are assumed to be ordered for orientation,
  CurvedTriangle(); // triangle with vertices at origin.
  CurvedTriangle(const Point3D &, const Point3D &, const Point3D &,const Vector3D &,const Vector3D &,const Vector3D &); // set vertices.

  // Copy constructor and assignment operator.
  CurvedTriangle(const CurvedTriangle &object);
  CurvedTriangle &operator=(const CurvedTriangle &rhs);

  // Destructor.
  virtual ~CurvedTriangle() = default;

  // String representation.
  std::string to_string() const override;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, float &t, ShadeInfo &s) const override;

  // Get bounding box.
  virtual BBox getBBox() const override;
};
