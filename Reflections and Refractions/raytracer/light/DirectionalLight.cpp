#include "DirectionalLight.hpp"


DirectionalLight::DirectionalLight(RGBColor color_, Vector3D direction_)
{
    color = color_;
    direction = direction_;
    direction.normalize();
}
    
Vector3D DirectionalLight::light_dir(Point3D hit_point, float &t) const
{
    t = kHugeValue;
    return -direction;
}

