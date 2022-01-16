#pragma once

#include <vector>

#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Image.hpp"

#include "../samplers/Sampler.hpp"

#include "../world/World.hpp"
#include "../world/ViewPlane.hpp"

#include "../acceleration/Acceleration.hpp"

#include "../materials/Material.hpp"

#include "../geometry/Plane.hpp"

class Camera;
class Ray;
class Sampler;
class ShadeInfo;
class World;

class Tracer
{
protected:
  World *world;

public:
  // Constructors.
  Tracer() = default; // initialize members.

  // Destructor.
  ~Tracer() = default; // free memory.

  void set_world(World *world_ptr);

  // Capture scene and save the image
  virtual Image *capture() const = 0;
};
