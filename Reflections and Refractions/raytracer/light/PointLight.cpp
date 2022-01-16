#include "PointLight.hpp"


PointLight::PointLight(RGBColor color_, Point3D source_)
{
    color = color_;
    source = source_;
}
    
Vector3D PointLight::light_dir(Point3D hit_point, float &t) const
{
    Vector3D dir = source - hit_point;
    t = source.distance(hit_point);
    dir.normalize();
    return dir;
}

