#include "BasicTracer.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>


  
Image* BasicTracer::capture() const
{
    using milli = std::chrono::milliseconds;
    auto start = std::chrono::high_resolution_clock::now();
    
    Sampler *sampler = world->sampler_ptr;
    ViewPlane &viewplane = world->vplane;
    Image* image = new Image(viewplane);

    std::vector<Ray> rays;
    for (int x = 0; x < viewplane.hres; x++)
    { // across.
        for (int y = 0; y < viewplane.vres; y++)
        { // down.
        // Get rays for the pixel from the sampler. The pixel color is the
        // weighted sum of the shades for each ray.
        RGBColor pixel_color(0);
        rays = sampler->get_rays(x, y);
        for (const auto &ray : rays)
        {
            float weight = ray.w; // ray weight for the pixel.
            ShadeInfo sinfo = world->hit_objects(ray);
            if (sinfo.hit)
            {
                if (world->light.size() == 0)
                {
                    // std::cout << "uwu nuzzles" << std::endl;
                    pixel_color += weight * sinfo.material_ptr->shade(sinfo,Beam(0,RGBColor(),Point3D(),Vector3D()));
                }
                else {

                for( Light* light: world->light)
                {
                    Beam beam = light->get_beam(sinfo);
                    
                    pixel_color += weight * sinfo.material_ptr->shade(sinfo, beam);
                }

                }
            }
            else
            { 
            pixel_color += weight * world->bg_color;
            }
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