#pragma once

/**
   This file declares the Phong class which represents a simple Phong
   material.

   It assigns a shade according to the Phong of the angle between the incoming
   ray direction and the normal at the hit point.

   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"

class Phong : public Material {
protected:
  RGBColor color; // the color of the material.

public:
  // Constructors.
  Phong();                          // set color to (0, 0, 0).
  Phong(float c);                   // set color to (c, c, c).
  Phong(float r, float g, float b); // set color to (r, g, b).
  Phong(const RGBColor &c);         // set color to c.

  // Copy constuctor and assignment operator.
  Phong(const Phong &other);
  Phong &operator=(const Phong &other);

  // Desctructor.
  virtual ~Phong() = default;

  /* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
  virtual RGBColor shade(const ShadeInfo &sinfo, const Beam beam) const override;
  
  // Get secondary rays.
  virtual std::vector<Ray> secondary_rays(const ShadeInfo &sinfo) const override;
};
