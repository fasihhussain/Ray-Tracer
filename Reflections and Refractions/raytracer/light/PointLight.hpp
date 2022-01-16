#pragma once

#include "Light.hpp"

#include "../utilities/RGBColor.hpp"
#include "../geometry/Geometry.hpp"

class PointLight : public Light
{
protected:
    Point3D source;
public:
    PointLight(RGBColor, Point3D);
    virtual Vector3D light_dir(Point3D hit_point, float &t) const override;
};
