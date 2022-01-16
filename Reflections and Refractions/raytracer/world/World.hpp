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
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"
#include "../materials/Cosine.hpp"
#include "../utilities/Ray.hpp"
#include "../samplers/Sampler.hpp"
#include "../geometry/Geometry.hpp"
#include "../cameras/Camera.hpp"
#include "../light/Light.hpp"

#include "ViewPlane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;

const int max_rec_depth = 3;

class World {
public:
  int rec_depth = 0;
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  std::vector<Light *> light;
  Camera *camera_ptr;
  Sampler *sampler_ptr;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light *light_ptr);
  void set_camera(Camera *c_ptr);

  bool shadow_ray(const ShadeInfo &sinfo, Light* light_ptr) const;
  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  RGBColor hit_objects( Ray &ray);
};
