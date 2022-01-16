#include "AreaLight.hpp"


AreaLight::AreaLight(RGBColor color_, Geometry *shape_)
{
    color = color_;
    shape = shape_;
}
    
Beam AreaLight::get_beam(const ShadeInfo sinfo) const
{
    Point3D source = shape->pick_random_point();
    Point3D hit_point = sinfo.hit_point;
    
    Vector3D dir = source - hit_point;
    dir.normalize();

    float t = source.distance(hit_point);

    return Beam(t, color, hit_point, dir);
}

