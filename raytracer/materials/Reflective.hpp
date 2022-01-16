#pragma once

/**
   This file declares the Reflective class which represents a simple Reflective
   material.

   It assigns a shade according to the Reflective of the angle between the incoming
   ray direction and the normal at the hit point.

   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"

class Reflective : public Material {
protected:
  RGBColor color; // the color of the material.

public:
  // Constructors.
  Reflective();                          // set color to (0, 0, 0).
  Reflective(float c);                   // set color to (c, c, c).
  Reflective(float r, float g, float b); // set color to (r, g, b).
  Reflective(const RGBColor &c);         // set color to c.

  // Copy constuctor and assignment operator.
  Reflective(const Reflective &other);
  Reflective &operator=(const Reflective &other);

  // Desctructor.
  virtual ~Reflective() = default;

  virtual RGBColor shade(const ShadeInfo &sinfo, const Beam beam) const override;
  
  // Get secondary rays.
  virtual std::vector<Ray> secondary_rays(const ShadeInfo &sinfo) const override;
};
