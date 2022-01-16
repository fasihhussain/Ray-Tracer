#pragma once

/**
   This file declares the ReflectiveTransparent class which represents a simple ReflectiveTransparent
   material.

   It assigns a shade according to the ReflectiveTransparent of the angle between the incoming
   ray direction and the normal at the hit point.

   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"

class ReflectiveTransparent : public Material {
protected:
  RGBColor color; // the color of the material.
  float refractive_index;

public:
  // Constructors.
  ReflectiveTransparent();                          // set color to (0, 0, 0).
  ReflectiveTransparent(float c);                   // set color to (c, c, c).
  ReflectiveTransparent(float r, float g, float b); // set color to (r, g, b).
  ReflectiveTransparent(const RGBColor &c);         // set color to c.
  ReflectiveTransparent(const RGBColor &c, float);  // set color to c.

  // Copy constuctor and assignment operator.
  ReflectiveTransparent(const ReflectiveTransparent &other);
  ReflectiveTransparent &operator=(const ReflectiveTransparent &other);

  // Desctructor.
  virtual ~ReflectiveTransparent() = default;

  /* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
  virtual RGBColor shade(const ShadeInfo &sinfo, const Beam beam) const override;
  
  // Get secondary rays.
  virtual std::vector<Ray> secondary_rays(const ShadeInfo &sinfo) const override;
};
