#include <iostream>
/*
g++ raytracer.cpp ./utilities/*.cpp ./world/*.cpp ./cameras/*.cpp ./geometry/*.cpp ./materials/*.cpp ./samplers/*.cpp ./build/buildChapter14.cpp
g++ raytracer.cpp ./utilities/*.cpp ./world/*.cpp ./cameras/*.cpp ./geometry/*.cpp ./materials/*.cpp ./samplers/*.cpp ./build/buildMVP.cpp
g++ raytracer.cpp ./utilities/*.cpp ./world/*.cpp ./cameras/*.cpp ./geometry/*.cpp ./materials/*.cpp ./samplers/*.cpp ./build/buildHelloWorld.cpp
*/

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"

int main(int argc, char **argv) {
  World world;
  world.build();

  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  std::vector<Ray> rays;
  for (int x = 0; x < viewplane.hres; x++) {   // across.
    for (int y = 0; y < viewplane.vres; y++) { // down.

      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.

      RGBColor pixel_color;

      rays = sampler->get_rays(x, y);
      
      for ( auto &ray : rays) {
        world.rec_depth = 0;
        pixel_color = world.hit_objects(ray);
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
      // std::cout << pixel_color << "\n";
    }
  }
  // Write image to file.
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";
  
  return 0;
}
