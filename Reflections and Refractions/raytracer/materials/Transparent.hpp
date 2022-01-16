#pragma once

/**
   This file declares the Cosine class which represents a simple cosine
   material.

   It assigns a shade according to the cosine of the angle between the incoming
   ray direction and the normal at the hit point.

   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

#include "../world/World.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"

class Transparent : public Material
{
protected:
    float ref_index;

public:
    // Constructors.
    Transparent();
    Transparent(float r);

    // Copy constuctor and assignment operator.
    Transparent(const Transparent &other);
    Transparent &operator=(const Transparent &other);

    // Desctructor.
    virtual ~Transparent() = default;

    /* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;

    // Get secondary rays.
    virtual std::vector<Ray> sec_rays(const ShadeInfo &sinfo,  const Ray prim_ray) const override;
};
