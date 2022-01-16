#include "PointLight.hpp"


PointLight::PointLight(RGBColor color_, Point3D source_)
{
    color = color_;
    source = source_;
}
    
Beam PointLight::get_beam(const ShadeInfo sinfo) const
{
    Point3D hit_point = sinfo.hit_point;
    
    Vector3D dir = source - hit_point;
    dir.normalize();

    float t = source.distance(hit_point);

    return Beam(t, color, hit_point, dir);
}

