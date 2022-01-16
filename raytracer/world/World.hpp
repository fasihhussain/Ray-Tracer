#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>

#include "../utilities/RGBColor.hpp"

#include "../tracers/Tracer.hpp"

#include "../lights/Light.hpp"

#include "ViewPlane.hpp"
#include "../acceleration/Acceleration.hpp"
#include "../geometry/Plane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Tracer;

class World
{
public:
    ViewPlane vplane;
    RGBColor bg_color;

    std::vector<Geometry *> geometry;
    std::vector<Plane *> planes;
    std::vector<Light *> light;

    Camera *camera_ptr;
    Sampler *sampler_ptr;
    Acceleration *accel_ptr;
    Tracer *tracer_ptr;

public:
    // Constructors.
    World(); // initialize members.

    // Destructor.
    ~World(); // free memory.

    // Add to the scene.
    void add_geometry(Geometry *geom_ptr);
    void add_plane(Plane *plane_ptr);
    void add_light(Light *light_ptr);

    void set_camera(Camera *c_ptr);
    void set_tracer(Tracer *tracer);

    // Build scene - add all geometry, materials, lights, viewplane, camera,
    // samplers, and acceleration structures
    void build();

    // Saves render in the ppm format
    void render(std::string);

    // Returns appropriate shading information corresponding to intersection of
    // the ray with the scene geometry.
    ShadeInfo hit_objects(const Ray &ray);
    void add_acceleration_structure();

    // loads the scene from PLY file
    void load_scene(std::string filename, bool load_colors, std::string mat_type, bool curved);
};
