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

class Glass : public Material
{
protected:
    RGBColor color; // the color of the material.
    float ref_index; // the refractive index of the material. 1.0 results in no bending of light.

public:
    // Constructors.
    Glass();                          // set color to (0, 0, 0).
    Glass(float c);                   // set color to (c, c, c).
    Glass(float r, float g, float b); // set color to (r, g, b).
    Glass(const RGBColor &c);         // set color to c.
    Glass(const RGBColor &c, float r);// set color to c.

    // Copy constuctor and assignment operator.
    Glass(const Glass &other);
    Glass &operator=(const Glass &other);

    // Desctructor.
    virtual ~Glass() = default;

    /* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;

    // Get secondary rays.
    virtual std::vector<Ray> sec_rays(const ShadeInfo &sinfo,  const Ray prim_ray) const override;
};
