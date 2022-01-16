#include "ShadowTracer.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

static int curr_depth;

ShadowTracer::ShadowTracer()
{
    rec_depth = 2;
}
  
ShadowTracer::ShadowTracer(int rec_depth_)
{
    rec_depth = rec_depth_;
}

  // Destructor.
ShadowTracer::~ShadowTracer()
{
}


RGBColor ShadowTracer::get_viewpoint(Ray view, int curr_depth) const
{
    RGBColor viewed_color(0);
    float weight = view.w;

    ShadeInfo sinfo = world->hit_objects(view);

    Material *material = sinfo.material_ptr;

    if (sinfo.hit)
    {
        for( Light* light: world->light)
        {
            Beam beam = light->get_beam(sinfo);
            Ray shadow_ray(
                sinfo.hit_point - kEpsilon * sinfo.ray.d,
                beam.direction
                );

            ShadeInfo shadowee = world->hit_objects( shadow_ray);
            if( !(shadowee.hit) || shadowee.t > beam.t)
            {
                viewed_color += weight * material->shade(sinfo, beam);
            }
        }
    }
    else
    {
        if (curr_depth == 0)
        {
            return weight * world->bg_color;
        }
        else
        {
            return black;
        }
    }
    
    if( curr_depth < rec_depth)
    {
        std::vector<Ray> sec_rays = material->secondary_rays(sinfo);

        curr_depth++;
        for( Ray ray: sec_rays) 
        {
            viewed_color += weight * get_viewpoint(ray, curr_depth);
        }
        curr_depth--;
    }

    return viewed_color;
}
  
Image* ShadowTracer::capture() const
{
    using milli = std::chrono::milliseconds;
    auto start = std::chrono::high_resolution_clock::now();
    
    Sampler *sampler = world->sampler_ptr;
    ViewPlane &viewplane = world->vplane;
    Image* image = new Image(viewplane);

    #pragma omp parallel for collapse(2)
    for (int x = 0; x < viewplane.hres; x++)
    { // across.
        for (int y = 0; y < viewplane.vres; y++)
        { // down.
        // Get rays for the pixel from the sampler. The pixel color is the
        // weighted sum of the shades for each ray.
        RGBColor pixel_color(0);
        std::vector<Ray> rays = sampler->get_rays(x, y);
        for (const auto &ray : rays)
        {
            pixel_color +=  get_viewpoint( ray, 0);
        }
        // Save color to image.
        image->set_pixel(x, y, pixel_color);
        // std::cout << x << "," << y << ": " << pixel_color.to_string() << "\n";
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Tracer.capture() took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " milliseconds\n";

    return image;
}
