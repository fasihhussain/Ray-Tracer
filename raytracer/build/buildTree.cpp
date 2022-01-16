#include <iostream>
#include <fstream>

#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/DoubleSidedTriangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"
#include "../samplers/RandomSampler.hpp"
#include "../samplers/Jittered.hpp"

#include "../lights/AreaLight.hpp"
#include "../lights/PointLight.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../tracers/AntiAliasing.hpp"

#include "../world/World.hpp"

void World::build(void)
{
    // view plane
    vplane.top_left.x = -0.5;
    vplane.top_left.y = 2.25;
    vplane.top_left.z = 3;
    vplane.bottom_right.x = 2.5;
    vplane.bottom_right.y = 0;
    vplane.bottom_right.z = 3;

    // setting the output resolution
    // 3/2.25 = 6/4.5 = 12/9
    vplane.hres = 12*20;
    vplane.vres = 9*20;
    this->set_tracer( new AntiAliasing(3,5));
    

    // adding lighting to the scene
    this->add_light(new AreaLight(white, new Sphere(Point3D(33, 33, 100), 10)));

    // colors
    bg_color = RGBColor(135.0 / 255, 206.0 / 255, 235.0 / 255.0); // background color.

    // camera and sampler.
    set_camera(new Parallel(0, 0, -1));
    // sampler_ptr = new Simple(camera_ptr, &vplane);
    sampler_ptr = new Regular(camera_ptr, &vplane, 4);
    // reading the file to add geometry
    load_scene("./build/models/tree.ply", false,"cosine",false);
    std::cout << "WORLD INITIALIZED" << std::endl;
}