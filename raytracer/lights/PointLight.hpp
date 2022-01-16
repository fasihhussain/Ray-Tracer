#pragma once

#include "Light.hpp"

class PointLight : public Light
{
protected:
    Point3D source;
public:
    PointLight(RGBColor, Point3D);
    virtual Beam get_beam(const ShadeInfo sinfo) const override;
};
