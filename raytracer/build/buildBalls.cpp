
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../lights/PointLight.hpp"
#include "../lights/AreaLight.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"

#include "../world/World.hpp"
#include "../tracers/Recursive.hpp"
void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.  
  bg_color = black;
  this->set_tracer(new Recursive(3));
  
  // // point light
  //add_light(new PointLight(white, Point3D(6, 6, 20)));
  
  // point light
  add_light(new AreaLight(white, new Sphere(Point3D(10, 10, 100), 10)));
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 50));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  for(int i = 0; i < 1000; ++i) 
  {  
    // spheres
    Sphere* sphere_ptr = new Sphere(
        Point3D(
            rand()%40 - 20, 
            rand()%40 - 20, 
            rand()%40 - 40
        ), 
        rand()/(float)RAND_MAX
    ); 
    // For >20k spheres
    // Sphere* sphere_ptr = new Sphere(
    // Point3D(
    //     rand()%400 - 200, 
    //     rand()%400 - 200, 
    //     rand()%400 - 400
    // ), 
    // rand()/(float)RAND_MAX
    // ); 
    sphere_ptr->set_material(new Cosine(
        RGBColor(
            rand()/(float)RAND_MAX, 
            rand()/(float)RAND_MAX, 
            rand()/(float)RAND_MAX
            )
        )
    );
    add_geometry(sphere_ptr);
  }
  

  // // plane
  // Plane* plane_ptr = new Plane(
  //     Point3D(0,-10,0), 
  //     Vector3D(0,1,0)
  //   ); 
  // plane_ptr->set_material(new Cosine(green));  // green
  // add_geometry(plane_ptr);
}
