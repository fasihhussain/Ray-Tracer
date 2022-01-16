#include "DirectionalLight.hpp"


DirectionalLight::DirectionalLight(RGBColor color_, Vector3D direction_)
{
    color = color_;
    direction = direction_;
    direction.normalize();
}
    
Beam DirectionalLight::get_beam(const ShadeInfo sinfo) const
{
    Point3D hit_point = sinfo.hit_point;
    Vector3D dir = -direction;

    return Beam(kHugeValue, color, hit_point, dir);
}

