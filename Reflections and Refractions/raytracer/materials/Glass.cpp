#include "Glass.hpp"

// Constructors.
Glass::Glass()
{
    ref_index = 1.2;
    color = RGBColor();
}

Glass::Glass(float c)
{
    ref_index = 1.2;
    color = RGBColor(c);
}

Glass::Glass(float r, float g, float b)
{
    ref_index = 1.2;
    color = RGBColor(r, g, b);
}

Glass::Glass(const RGBColor &c)
{
    ref_index = 1.2;
    color = c;
}

Glass::Glass(const RGBColor &c, float r)
{
    color = c;
    ref_index = r;
}

Glass::Glass(const Glass &other)
{
    color = other.color;
    ref_index = other.ref_index;
}

Glass &Glass::operator=(const Glass &other)
{
    color = other.color;
    ref_index = other.ref_index;
    return *this;
}

std::vector<Ray> Glass::sec_rays(const ShadeInfo &sinfo, const Ray prim_ray) const
{
    std::vector<Ray> sec_ray;

    if (-(sinfo.normal*prim_ray.d) > 0)
    {
        Ray ref_ray;
        ref_ray.d = prim_ray.d - 2*(sinfo.normal*prim_ray.d) * sinfo.normal;
        ref_ray.o = sinfo.hit_point + kEpsilon * sinfo.normal;
        ref_ray.w = 0.1;
        sec_ray.push_back(ref_ray);

        Ray refr_ray;
        float cosine_inc = -(sinfo.normal*prim_ray.d);
        float sine_ref = ref_index*ref_index * (1-cosine_inc*cosine_inc);
        refr_ray.d = ref_index*prim_ray.d + (ref_index*cosine_inc - sqrt(1 - sine_ref*sine_ref))*sinfo.normal;
        refr_ray.o = sinfo.hit_point - kEpsilon * sinfo.normal;
        refr_ray.w = 1.0;
        sec_ray.push_back(refr_ray);
    }
    else
    {
        Ray ref_ray;
        ref_ray.d = prim_ray.d - 2*(sinfo.normal*prim_ray.d) * sinfo.normal;
        ref_ray.o = sinfo.hit_point - kEpsilon * sinfo.normal;
        ref_ray.w = 0.1;
        sec_ray.push_back(ref_ray);

        float refr_inv = 1/ref_index;
        Ray refr_ray;
        float cosine_inc = (sinfo.normal*prim_ray.d);
        float sine_ref = refr_inv*refr_inv * (1-cosine_inc*cosine_inc);
        refr_ray.d = refr_inv*prim_ray.d + (refr_inv*cosine_inc - sqrt(1 - sine_ref*sine_ref))*-sinfo.normal;
        refr_ray.o = sinfo.hit_point - kEpsilon * -sinfo.normal;
        refr_ray.w = 1.0;
        sec_ray.push_back(refr_ray);
    }
    return sec_ray;
}

RGBColor Glass::shade(const ShadeInfo &sinfo) const
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
            lum = -(sinfo.ray.d*dir);
            if (lum < 0) 
                lum = 0;
            ishade += lum*color + pow(lum, 50.0)*light->color;
        }
    }
    return ishade + 0.1*color;
}
