#pragma once

#include "Light.hpp"

#include "../utilities/RGBColor.hpp"
#include "../geometry/Geometry.hpp"

class Light
{
public:
    // the color of the light.
    RGBColor color; 

    // returns the direction of the ray's source.
    virtual Vector3D light_dir(Point3D hit_point, float &t) const = 0;
};
