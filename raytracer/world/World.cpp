#include <iostream>
#include <fstream>

#include "World.hpp"

#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"

#include "../geometry/Geometry.hpp"
#include "../geometry/CurvedTriangle.hpp"
#include "../geometry/DoubleSidedTriangle.hpp"
#include "../geometry/DoubleSidedCurvedTriangle.hpp"
#include "../geometry/Triangle.hpp"

#include "../cameras/Camera.hpp"

#include "../samplers/Sampler.hpp"
#include "../samplers/Simple.hpp"

#include "../acceleration/BVH.hpp"
#include "../acceleration/Grid.hpp"

#include "../happly/happly.h"

#include "../materials/Cosine.hpp"
#include "../materials/Phong.hpp"
World::World()
{
    accel_ptr = nullptr;
    vplane = ViewPlane();
    bg_color = RGBColor(0, 0, 0);
    geometry.clear();
    camera_ptr = nullptr;
    sampler_ptr = new Simple(nullptr, &vplane);
}

World::~World()
{
    for (auto &geom : geometry)
    {
        delete geom;
    }
    if (camera_ptr)
    {
        delete camera_ptr;
        camera_ptr = nullptr;
    }
    if (sampler_ptr)
    {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
    if (tracer_ptr)
    {
        delete tracer_ptr;
        tracer_ptr = nullptr;
    }
}

void World::set_tracer(Tracer *tracer)
{
    tracer_ptr = tracer;
    tracer_ptr->set_world(this);
}
void World::add_geometry(Geometry *geom_ptr)
{
    geometry.push_back(geom_ptr);
}
void World::add_light(Light *light_ptr)
{
    light.push_back(light_ptr);
}
void World::add_plane(Plane *plane_ptr)
{
    planes.push_back(plane_ptr);
}
void World::set_camera(Camera *c_ptr)
{
    camera_ptr = c_ptr;
}

// void World::build() {
//   // TODO: implement this function.
// }

void World::render(std::string filename)
{
    Image *image = tracer_ptr->capture();
    image->write_ppm(filename);
}

ShadeInfo World::hit_objects(const Ray &ray)
{
    ShadeInfo shade_info(*this);
    shade_info.hit = false;
    shade_info.ray = ray;
    shade_info.t = kHugeValue;
    // Initialize t (min hitpoint) as a large number.
    // float t = kHugeValue;
    if (accel_ptr)
    {
        accel_ptr->hit_objects(ray, shade_info);
    }
    else
    {
        for (auto &geom : geometry)
        {
            geom->hit(ray, shade_info.t, shade_info);
        }
    }
    // std::cout << "hit_objects" << std::endl;
    for (auto &geom : planes)
    {
        geom->hit(ray, shade_info.t, shade_info);
        // std::cout << "hit plane" << std::endl;
    }

    return shade_info;
}

void World::add_acceleration_structure()
{
    if (accel_ptr)
    {
        delete accel_ptr;
        accel_ptr = nullptr;
    }
    // accel_ptr = new BVHTree(geometry);
    accel_ptr = new Grid(geometry);
}

Material* make_material_of_color(std::string mat_type,RGBColor color)
{
    if (mat_type == "phong")
    {
        std::cout <<"uwu"<<std::endl;
        return new Phong(color);
    }
    else if (mat_type == "cosine")
    {
        return new Cosine(color);
    }
    else
    {
        std::cout << "Error: material type not found" << std::endl;
        return nullptr;
    }
}


void World::load_scene(std::string filename, bool load_colors,std::string mat_type,bool curved)
{
    std::ifstream infile(filename);

    int n_points, n_faces;
    float x, y, z, nx, ny, nz, red, green, blue, alpha;
    std::string data;

    std::getline(infile, data);         // ply
    std::getline(infile, data);         // format ascii 1.0
    std::getline(infile, data);         // comment Created by Blender 3.0.0 - www.blender.org
    infile >> data >> data >> n_points; // element vertex N_POINTS
    std::getline(infile, data);         // \n
    std::getline(infile, data);         // property float x
    std::getline(infile, data);         // property float y
    std::getline(infile, data);         // property float z
    std::getline(infile, data);         // property float nx
    std::getline(infile, data);         // property float ny
    std::getline(infile, data);         // property float nz
    std::getline(infile, data);         // property uchar red
    std::getline(infile, data);         // property uchar green
    std::getline(infile, data);         // property uchar blue
    std::getline(infile, data);         // property uchar alpha
    infile >> data >> data >> n_faces;  // element face N_FACES
    std::getline(infile, data);         // \n
    std::getline(infile, data);         // property list uchar uint vertex_indices
    std::getline(infile, data);         // end_header

    Point3D *points = new Point3D[n_points];
    RGBColor *colors = new RGBColor[n_points];
    Vector3D *normals = new Vector3D[n_points];

    std::cout << "N_POINTS: " << n_points << std::endl;
    std::cout << "N_FACES: " << n_faces << std::endl;

    // reading the vertices
    for (int i = 0; i < n_points; i++)
    {
        infile >> x >> z >> y >> nx >> ny >> nz >> red >> green >> blue >> alpha;

        points[i] = Point3D(x, y, z);

        normals[i] = Vector3D(nx, ny, nz);
        normals[i].normalize();

        // assigning vertex colors
        if (load_colors)
        {
            colors[i] = RGBColor(red / (float)256.0, green / (float)256.0, blue / (float)256.0); // actual color from ply file
        }
        else
        {
            colors[i] = RGBColor(1.0); // white color
        }
    }

    int n, a, b, c;
    RGBColor face_color;
    Geometry *triangle_ptr;

    // reading the faces
    for (int i = 0; i < n_faces; i++)
    {
        infile >> n >> a >> b >> c;

        face_color = RGBColor(colors[a] / (float)3.0) + (colors[b] / (float)3.0) + (colors[c] / (float)3.0);
        if (curved) {
        triangle_ptr = new DoubleSidedCurvedTriangle(points[a], points[b], points[c], normals[a], normals[b], normals[c]);
        }
        else {
            triangle_ptr = new DoubleSidedTriangle(points[a], points[b], points[c]);
        }
        triangle_ptr->set_material(make_material_of_color(mat_type,face_color));

        add_geometry(triangle_ptr);
    }

    infile.close();
}