#pragma once

/**
   This file declares the Material class which is an abstract class for concrete
   materials to inherit from.

   Courtesy Kevin Suffern.
*/

#include <vector>
#include "../utilities/Ray.hpp"

class RGBColor;
class ShadeInfo;

class Material
{
public:
    // Constructors.
    Material() = default; // does nothing.

    // Copy constuctor and assignment operator.
    Material(const Material &other) = default;
    Material &operator=(const Material &other) = default;

    // Desctructor.
    virtual ~Material() = default;

    // Get color.
    virtual RGBColor shade(const ShadeInfo &sinfo) const = 0;

    // Get secondary rays.
    virtual std::vector<Ray> sec_rays(const ShadeInfo &sinfo,  const Ray prim_ray) const = 0;

};