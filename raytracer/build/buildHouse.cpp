#include <iostream>
#include <fstream>

#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/DoubleSidedCurvedTriangle.hpp"
#include "../geometry/DoubleSidedTriangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Phong.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"
#include "../samplers/RandomSampler.hpp"
#include "../samplers/Jittered.hpp"

#include "../lights/AreaLight.hpp"
#include "../lights/PointLight.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"
#include "../tracers/AntiAliasing.hpp"
void World::build(void)
{
    // view plane
    vplane.top_left.x = -3;
    vplane.top_left.y = 3;
    vplane.top_left.z = 3;
    vplane.bottom_right.x = 2;
    vplane.bottom_right.y = 0;
    vplane.bottom_right.z = 3;
    vplane.hres = 1500;
    vplane.vres = 900;
    
    this->set_tracer( new AntiAliasing(3,5));

    this->add_light(new AreaLight(white, new Sphere(Point3D(33, 33, 100), 10)));
    this->add_light(new AreaLight(white, new Sphere(Point3D(-33, 33, 100), 10)));
    this->add_light(new AreaLight(white, new Sphere(Point3D(33, -33, 100), 10)));

    // sun
    this->add_light(new AreaLight(white, new Sphere(Point3D(1, 2, 1), 0.1)));

    // colors
    RGBColor sun(0.5, 0.3, 0); // yellow

    // spheres
    Sphere *sphere_ptr1 = new Sphere(Point3D(1, 2, 1), 0.1);
    sphere_ptr1->set_material(new Cosine(sun)); // yellow
    add_geometry(sphere_ptr1);

    // colors
    bg_color = RGBColor(80.0 / 255, 100.0 / 255, 135.0 / 255.0); // background color.

    // camera and sampler.
    set_camera(new Parallel(0, 0, -1));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    // reading the file to add geometry
    load_scene("./build/models/house.ply", true, "phong", true);
    std::cout << "WORLD INITIALIZED" << std::endl;
}