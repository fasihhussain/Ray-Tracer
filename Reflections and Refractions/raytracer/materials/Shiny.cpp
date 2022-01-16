#include "Shiny.hpp"

// Constructors.
Shiny::Shiny()
{
    polish = 1.0;
    color = RGBColor();
}

Shiny::Shiny(float c)
{
    polish = 1.0;
    color = RGBColor(c);
}

Shiny::Shiny(float r, float g, float b)
{
    polish = 1.0;
    color = RGBColor(r, g, b);
}

Shiny::Shiny(const RGBColor &c)
{
    polish = 1.0;
    color = c;
}

Shiny::Shiny(const RGBColor &c, float p)
{
    color = c;
    polish = p;
}

Shiny::Shiny(const Shiny &other)
{
    polish = other.polish;
    color = other.color;
}

Shiny &Shiny::operator=(const Shiny &other)
{
    polish = other.polish;
    color = other.color;
    return *this;
}


std::vector<Ray> Shiny::sec_rays(const ShadeInfo &sinfo, const Ray prim_ray) const
{
    std::vector<Ray> sec_ray;

    Ray ref_ray;
    ref_ray.d = prim_ray.d - 2*(sinfo.normal*prim_ray.d) * sinfo.normal;
    ref_ray.o = sinfo.hit_point + kEpsilon*sinfo.normal;
    ref_ray.w = polish;
    sec_ray.push_back(ref_ray);
    return sec_ray;
}

RGBColor Shiny::shade(const ShadeInfo &sinfo) const
{
    RGBColor ishade(0,0,0);

    float lum, t;
    Vector3D dir;
    const std::vector<Light*> *lights = &(sinfo.w->light);

    for( Light* light: *lights)
    {
        if (sinfo.w->shadow_ray(sinfo, light))
        {
            dir = light->light_dir(sinfo.hit_point, t);
            dir = 2*(sinfo.normal*dir) * sinfo.normal - dir;
            lum = (-sinfo.ray.d*dir);
            if (lum < 0) lum = 0;
            ishade += lum*color + pow(lum, 30.0)*light->color;
        }
    }
    return ishade + 0.2*color;
}
