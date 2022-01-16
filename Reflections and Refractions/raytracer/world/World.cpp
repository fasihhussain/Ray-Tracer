#include "World.hpp"
#include <iostream>
  
World::World()
{
}

World::~World()
{
    delete camera_ptr;
    delete sampler_ptr;
    geometry.clear();
}

void World::add_light(Light *light_ptr)
{
    light.push_back(light_ptr);
}

void World::add_geometry(Geometry *geom_ptr)
{
    geometry.push_back(geom_ptr);
}
  
void World::set_camera(Camera *c_ptr)
{
    camera_ptr = c_ptr;
}

bool World::shadow_ray(const ShadeInfo &sinfo, Light* light_ptr) const
{
    float t;
    Ray ray;
    ray.d = light_ptr->light_dir(sinfo.hit_point, t); 
    if (ray.d * sinfo.normal > 0)
    {
        ray.o = sinfo.hit_point + kEpsilon * sinfo.normal;
        for( Geometry* object: geometry)
        {
            ShadeInfo sinfo_(*this);
            float t_;
            if (object->hit(ray, t_, sinfo_)) 
            {
                if (t_ < t) 
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

RGBColor World::hit_objects( Ray &ray)
{
    RGBColor color(0,0,0);
    ShadeInfo sinfo(*this);
    float t = kHugeValue;
    bool hit = false;

    for( Geometry* object: geometry)
    {
        ShadeInfo sinfo_(*this);
        float t_;
        if (object->hit(ray, t_, sinfo_)) 
        {
            if (t_ < t) 
            {
                hit = true;
                sinfo = sinfo_;
                t = t_;
            }
        }
    }
    if (hit == false && rec_depth == 0)
        return bg_color;
    if (hit == false && rec_depth > 0)
        return color;

    color += sinfo.material_ptr->shade(sinfo);
    if ( rec_depth < max_rec_depth)
    {
        rec_depth++;
        std::vector<Ray> sec_rays = sinfo.material_ptr->sec_rays(sinfo, ray);
        for( Ray sec_ray: sec_rays)
        {
            color += sec_ray.w * hit_objects(sec_ray);
        }
        rec_depth--;
    }
    return color;
}