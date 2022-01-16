#include <iostream>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
int main(int argc, char **argv)
{
  srand(time(NULL));
  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();
  World world;
  world.build();
  world.add_acceleration_structure();
  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  #pragma omp parallel for schedule(dynamic) 
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
        float weight = ray.w; // ray weight for the pixel.
        ShadeInfo sinfo = world.hit_objects(ray);
        if (sinfo.hit)
        {
          pixel_color += weight * sinfo.material_ptr->shade(sinfo);
        }
        else
        { 
          pixel_color += weight * world.bg_color;
          // std::cout << pixel_color.to_string() << std::endl;
        }
        // std::cout << sinfo.hit << std::endl;
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
      // std::cout << x << "," << y << ": " << pixel_color.to_string() << "\n";
    }
  }
  // Write image to file.
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";
  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "myFunction() took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " milliseconds\n";
  return 0;
}
