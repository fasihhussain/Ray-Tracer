#pragma once

#include "../geometry/Geometry.hpp"
#include "Light.hpp"

class AreaLight : public Light
{
protected:
    Geometry *shape;
public:
    AreaLight(RGBColor, Geometry*);
    virtual Beam get_beam(const ShadeInfo sinfo) const override;
};
