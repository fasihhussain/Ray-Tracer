#include "Cosine.hpp"
#include <iostream>

// Constructors.
Cosine::Cosine()
{
    color = RGBColor();
}

Cosine::Cosine(float c)
{
    color = RGBColor(c);
}

Cosine::Cosine(float r, float g, float b)
{
    color = RGBColor(r, g, b);
}

Cosine::Cosine(const RGBColor &c)
{
    color = c;
}

Cosine::Cosine(const Cosine &other)
{
    color = other.color;
}

Cosine &Cosine::operator=(const Cosine &other)
{
    color = other.color;
    return *this;
}

std::vector<Ray> Cosine::sec_rays(const ShadeInfo &sinfo,  const Ray prim_ray) const
{
    std::vector<Ray> sec_ray;
    return sec_ray;
}


/*
    Returned shade is: color * cos \theta.
    \theta is the angle between the normal at the hit pont and the ray.
    Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
*/

RGBColor Cosine::shade(const ShadeInfo &sinfo) const
{
    RGBColor ishade(0,0,0);

    Vector3D a = sinfo.normal;
    Vector3D b = -sinfo.ray.d;

    a.normalize();
    b.normalize();

    float lum, t;
    Vector3D inc, ref;
    const std::vector<Light*> *lights = &(sinfo.w->light);

    for( Light* light: *lights)
    {
        if (sinfo.w->shadow_ray(sinfo, light))
        {
            inc = light->light_dir(sinfo.hit_point, t);
            ref = 2*(sinfo.normal*inc) * sinfo.normal - inc;
            lum = (-sinfo.ray.d*ref);
            if (lum < 0) lum = 0;
            ishade += (a*b)*color + lum*light->color;
        }
    }

    return ishade;
}
