#pragma once

#include "Light.hpp"
#include "../utilities/Constants.hpp"

class DirectionalLight : public Light
{
protected:
    Vector3D direction;
public:
    DirectionalLight(RGBColor, Vector3D);
    virtual Beam get_beam(const ShadeInfo sinfo) const override;
};
