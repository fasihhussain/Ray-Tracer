#pragma once

/**
   This file declares the Material class which is an abstract class for concrete
   materials to inherit from.

   Courtesy Kevin Suffern.
*/

#include <vector>
#include "../utilities/Ray.hpp"
#include "../lights/Beam.hpp"

class RGBColor;
class ShadeInfo;

class Material {
public:

  // Constructors.
  Material() = default; // does nothing.

  // Copy constuctor and assignment operator.
  Material(const Material &other) = default;
  Material &operator=(const Material &other) = default;

  // Desctructor.
  virtual ~Material() = default;

  // Get color.
  // most materials are light position dependent thus the beam argument
  // if the shadow ray is blocked, the tracer will not waste time to call this function
  virtual RGBColor shade(const ShadeInfo &sinfo, const Beam beam) const = 0;

  // Get secondary rays.
  // the sum of weights of secondary rays should be less than 1
  // otherwise the image will not converge
  virtual std::vector<Ray> secondary_rays(const ShadeInfo &sinfo) const = 0;
};
