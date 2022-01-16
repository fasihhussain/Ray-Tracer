
/**
   This builds a scene that consists of 35 shaded spheres and a plane.
   Perspective viewing is used with a single sample per pixel.
   The spheres are the same as those in the Chapter 14 page one image. 

   Courtesy Kevin Suffern.
*/

#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../tracers/BasicTracer.hpp"
#include "../world/World.hpp"

void World::build(void)
{
    // view plane
    vplane.top_left.x = -200;
    vplane.top_left.y = 200;
    vplane.top_left.z = 100;
    vplane.bottom_right.x = 200;
    vplane.bottom_right.y = -200;
    vplane.bottom_right.z = 100;
    vplane.hres = 400;
    vplane.vres = 400;
    this->set_tracer(new BasicTracer());

    // colors
    RGBColor colors[10];
    colors[0] = RGBColor(1, 1, 0);          // yellow
    colors[1] = RGBColor(0.71, 0.40, 0.16); // brown
    colors[2] = RGBColor(0.0, 0.41, 0.41);  // darkGreen
    colors[3] = RGBColor(1, 0.75, 0);       // orange
    colors[4] = RGBColor(0, 0.6, 0.3);      // green
    colors[5] = RGBColor(0.65, 1, 0.30);    // light green
    colors[6] = RGBColor(0.61, 0.61, 0);    // dark yellow
    colors[7] = RGBColor(0.65, 0.3, 1);     // light purple
    colors[8] = RGBColor(0.5, 0, 1);        // dark purple
    colors[9] = RGBColor(0.25);             // grey

    bg_color = colors[9]; // background color.

    // camera and sampler.
    set_camera(new Parallel(0, 0, -1));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    unsigned int SEED = 123;
    std::srand(SEED);

    int n = 10000;

    int x_range = vplane.bottom_right.x - vplane.top_left.x;
    int y_range = vplane.top_left.y - vplane.bottom_right.y;

    Triangle *triangle_ptr;

    Point3D a;
    Point3D b;
    Point3D c;

    int x, y, color;

    for (int i = 0; i < n; i++)
    {
        x = (std::rand() % x_range) + vplane.top_left.x;
        y = (std::rand() % y_range) + vplane.bottom_right.y;
        a = Point3D(x, y, 0);

        x = (std::rand() % x_range) + vplane.top_left.x;
        y = (std::rand() % y_range) + vplane.bottom_right.y;
        b = Point3D(x, y, 0);

        x = (std::rand() % x_range) + vplane.top_left.x;
        y = (std::rand() % y_range) + vplane.bottom_right.y;
        c = Point3D(x, y, 0);

        float area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

        if (area > 0)
            triangle_ptr = new Triangle(a, b, c);
        else
            triangle_ptr = new Triangle(a, c, b);
        triangle_ptr->set_material(new Cosine(colors[std::rand() % 9]));
        add_geometry(triangle_ptr);
    }
}