#pragma once

#include <omp.h>
#include "Tracer.hpp"

class Camera;
class Ray;
class Sampler;
class ShadeInfo;
class World;

class ShadowTracer: public Tracer {
protected:
  // Keeps track of recursion depth of get_viewpoint()
  int rec_depth;
  
  // Calculates shade from a given viewing ray recursively
  RGBColor get_viewpoint( Ray ray, int curr_depth) const;

public:
  // Constructors.
  ShadowTracer();     // initialize members.
  ShadowTracer(int);  // initialize members.

  // Destructor.
  ~ShadowTracer(); // free memory.
  
  // Capture scene and save the image
  virtual Image* capture() const override;
};
