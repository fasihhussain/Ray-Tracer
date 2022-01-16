
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../light/PointLight.hpp"
#include "../light/DirectionalLight.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Transparent.hpp"
#include "../materials/Glass.hpp"

#include "../samplers/Simple.hpp"
// #include "../samplers/Re"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"

#include "../world/World.hpp"

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 500;
  vplane.vres = 500;

  // Background color.  
  bg_color = black;
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 20));
  // sampler_ptr = new Simple(camera_ptr, &vplane);
  sampler_ptr = new Regular(camera_ptr, &vplane,3);
	
  // sphere
  Sphere* sphere_ptr1 = new Sphere(Point3D(0, 14, -10), 4); 
  sphere_ptr1->set_material(new Cosine(red));
  add_geometry(sphere_ptr1);
  
  // sphere
  Sphere* sphere_ptr2 = new Sphere(Point3D(0, 4, 5), 3); 
  sphere_ptr2->set_material(new Transparent());
  add_geometry(sphere_ptr2);
  
  // sphere
  Sphere* sphere_ptr3 = new Sphere(Point3D(8, 4, 6), 3); 
  sphere_ptr3->set_material(new Glass(yellow));
  add_geometry(sphere_ptr3);
  
  // point light
  PointLight* light_ptr1 = new PointLight(white, Point3D(6, 6, 20));
  add_light(light_ptr1);
  
  // point light
  PointLight* light_ptr2 = new PointLight(white, Point3D(-6, 20, 20));
  add_light(light_ptr2);

  // triangle
  Point3D a(2.5, -3, -6); 
  Point3D b(14, 1, -7); 
  Point3D c(8.5, 7, -6.5); 

  Triangle* triangle_ptr = new Triangle(a, b, c);
  triangle_ptr->set_material(new Cosine(blue));
  add_geometry(triangle_ptr);

  // plane
  Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(0, 10, 2)); 
  plane_ptr->set_material(new Cosine(green));  // green
  add_geometry(plane_ptr);
}
