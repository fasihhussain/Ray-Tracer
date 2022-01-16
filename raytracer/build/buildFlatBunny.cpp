#include <iostream>
#include <fstream>

#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"
#include "../happly/happly.h"
#include "../samplers/RandomSampler.hpp"
#include "../samplers/Regular.hpp"
#include "../tracers/BasicTracer.hpp"
void World::build(void)
{
    vplane.top_left.x = -0.12;
    vplane.top_left.y = 0.2;
    vplane.top_left.z = 1;

    vplane.bottom_right.x = 0.08;
    vplane.bottom_right.y = 0;
    vplane.bottom_right.z = 1;
    vplane.hres = 400;
    vplane.vres = 400;
    this->set_tracer( new BasicTracer());

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
    sampler_ptr = new Regular(camera_ptr, &vplane, 4);

    // reading the file to add geometry
    happly::PLYData plyIn("build/models/bun_zipper.ply");

    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
    std::vector<Point3D> points;
    std::vector<Vector3D> normals;
    // Iterate through all points
    for (size_t i = 0; i < vPos.size(); i++)
    {
        Point3D point = Point3D(vPos[i][0], vPos[i][1], vPos[i][2]);
        points.push_back(point);
        normals.push_back(Vector3D());
    }

    Material *mat = new Cosine(colors[4]);
    for (size_t i = 0; i < fInd.size(); i++)
    {
        // Get the indices of the points of the face
        std::vector<size_t> faceIndices = fInd[i];
        // Create a triangle
        Point3D v0 = points[faceIndices[0]];
        Point3D v1 = points[faceIndices[1]];
        Point3D v2 = points[faceIndices[2]];
        // Compute normal
        Triangle *triangle = new Triangle(v0, v1, v2);
        // Set the color of the triangle
        triangle->set_material(mat);
        // Add the triangle to the world
        add_geometry(triangle);

    }
}