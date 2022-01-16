#pragma once

/**
   This file declares the Transparent class which represents a simple Transparent
   material.

   It assigns a shade according to the Transparent of the angle between the incoming
   ray direction and the normal at the hit point.

   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"

class Transparent : public Material {
protected:
  RGBColor color; // the color of the material.
  float refractive_index;

public:
  // Constructors.
  Transparent();                          // set color to (0, 0, 0).
  Transparent(float c);                   // set color to (c, c, c).
  Transparent(float r, float g, float b); // set color to (r, g, b).
  Transparent(const RGBColor &c);         // set color to c.
  Transparent(const RGBColor &c, float);  // set color to c.

  // Copy constuctor and assignment operator.
  Transparent(const Transparent &other);
  Transparent &operator=(const Transparent &other);

  // Desctructor.
  virtual ~Transparent() = default;

  virtual RGBColor shade(const ShadeInfo &sinfo, const Beam beam) const override;
  
  // Get secondary rays.
  virtual std::vector<Ray> secondary_rays(const ShadeInfo &sinfo) const override;
};
