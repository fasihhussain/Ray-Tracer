#pragma once

#include "Beam.hpp"
#include "../utilities/ShadeInfo.hpp"

class Light
{
public:
    // the color of the light.
    RGBColor color; 

    // returns the beam from this light.
    virtual Beam get_beam(const ShadeInfo sinfo) const = 0;
};
