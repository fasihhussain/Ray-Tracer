#pragma once

#include "Light.hpp"

#include "../utilities/RGBColor.hpp"
#include "../geometry/Geometry.hpp"

class DirectionalLight : public Light
{
protected:
    Vector3D direction;
public:
    DirectionalLight(RGBColor, Vector3D);
    virtual Vector3D light_dir(Point3D hit_point, float &t) const override;
};
