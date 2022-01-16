#include "Transparent.hpp"

// Constructors.
Transparent::Transparent()
{
    ref_index = 1.2;
}

Transparent::Transparent(float r)
{
    ref_index = r;
}

Transparent::Transparent(const Transparent &other)
{
    ref_index = other.ref_index;
}

Transparent &Transparent::operator=(const Transparent &other)
{
    ref_index = other.ref_index;
    return *this;
}

std::vector<Ray> Transparent::sec_rays(const ShadeInfo &sinfo, const Ray prim_ray) const
{
    std::vector<Ray> sec_ray;

    if (-(sinfo.normal*prim_ray.d) > 0)
    {
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

RGBColor Transparent::shade(const ShadeInfo &sinfo) const
{
    RGBColor ishade(0,0,0);
    return ishade;
}
